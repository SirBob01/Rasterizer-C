#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "math.h"

void create_framebuffer(framebuffer_t *framebuffer,
                        unsigned width,
                        unsigned height) {
    assert(framebuffer != NULL);
    framebuffer->color = malloc(width * height * sizeof(color_t));
    framebuffer->depth = malloc(width * height * sizeof(float));
    framebuffer->width = width;
    framebuffer->height = height;
    assert(framebuffer->color != NULL);
    assert(framebuffer->depth != NULL);
}

void destroy_framebuffer(framebuffer_t *framebuffer) {
    assert(framebuffer != NULL);
    assert(framebuffer->color != NULL);
    free(framebuffer->color);
    free(framebuffer->depth);
}

void draw_mesh_framebuffer(framebuffer_t *framebuffer,
                           const mesh_t *mesh,
                           const mat4_t *model,
                           const mat4_t *view,
                           const mat4_t *projection) {
    mat4_t mv, mvp;
    mul_mat4(view, model, &mv);
    mul_mat4(projection, &mv, &mvp);

    for (unsigned i = 0; i < mesh->index_count; i += 3) {
        vertex_t *a = mesh->vertices + mesh->indices[i + 0];
        vertex_t *b = mesh->vertices + mesh->indices[i + 1];
        vertex_t *c = mesh->vertices + mesh->indices[i + 2];

        // Convert model space to clip space
        vec4_t ca, cb, cc;
        local_to_clip(&a->position, &mvp, &ca);
        local_to_clip(&b->position, &mvp, &cb);
        local_to_clip(&c->position, &mvp, &cc);

        // Convert clip space to screen space
        vec2_t sa, sb, sc;
        clip_to_screen(&ca, framebuffer->width, framebuffer->height, &sa);
        clip_to_screen(&cb, framebuffer->width, framebuffer->height, &sb);
        clip_to_screen(&cc, framebuffer->width, framebuffer->height, &sc);

        // Rasterize
        rasterize_triangle_framebuffer(framebuffer,
                                       &sa,
                                       &sb,
                                       &sc,
                                       &a->color,
                                       &b->color,
                                       &c->color,
                                       ca.z,
                                       cb.z,
                                       cc.z);
    }
}

void rasterize_triangle_framebuffer(framebuffer_t *framebuffer,
                                    const vec2_t *a,
                                    const vec2_t *b,
                                    const vec2_t *c,
                                    const color_t *ca,
                                    const color_t *cb,
                                    const color_t *cc,
                                    float da,
                                    float db,
                                    float dc) {
    // Compute bounding rect of triangle
    vec2_t vmin = {
        .x = min(min(a->x, b->x), c->x),
        .y = min(min(a->y, b->y), c->y),
    };
    vec2_t vmax = {
        .x = max(max(a->x + 1, b->x + 1), c->x + 1),
        .y = max(max(a->y + 1, b->y + 1), c->y + 1),
    };

    // Scan each pixel
    float eps = 1e-5;
    for (unsigned i = vmin.x; i <= vmax.x; i++) {
        for (unsigned j = vmin.y; j <= vmax.y; j++) {
            vec2_t position = {
                .x = i,
                .y = j,
            };

            vec3_t barypos;
            compute_barycentric(a, b, c, &position, &barypos);
            if (barypos.x >= -eps && barypos.y >= -eps && barypos.z >= -eps) {
                // Interpolate colors
                color_t color = {
                    .r = ca->r * barypos.x + cb->r * barypos.y +
                         cc->r * barypos.z,
                    .g = ca->g * barypos.x + cb->g * barypos.y +
                         cc->g * barypos.z,
                    .b = ca->b * barypos.x + cb->b * barypos.y +
                         cc->b * barypos.z,
                    .a = ca->a * barypos.x + cb->a * barypos.y +
                         cc->a * barypos.z,
                };

                // Interpolate depth
                float depth = barypos.x * da + barypos.y * db + barypos.z * dc;

                // Depth culling
                unsigned offset = j * framebuffer->width + i;
                if (depth < framebuffer->depth[offset]) {
                    write_framebuffer(framebuffer, &position, &color, depth);
                }
            }
        }
    }
}

void write_framebuffer(framebuffer_t *framebuffer,
                       const vec2_t *position,
                       const color_t *color,
                       float depth) {
    unsigned row = position->y;
    unsigned col = position->x;
    unsigned offset = row * framebuffer->width + col;
    memcpy(framebuffer->color + offset, color, sizeof(color_t));
    framebuffer->depth[offset] = depth;
}

void clear_framebuffer(framebuffer_t *framebuffer, const color_t *clear_value) {
    unsigned dimensions = framebuffer->width * framebuffer->height;
    for (unsigned offset = 0; offset < dimensions; offset++) {
        memcpy(framebuffer->color + offset, clear_value, sizeof(color_t));
        framebuffer->depth[offset] = FLT_MAX;
    }
}