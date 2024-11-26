#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "math.h"

void create_framebuffer(framebuffer_t *framebuffer,
                        unsigned width,
                        unsigned height) {
    framebuffer->buffer = malloc(width * height * PIXEL_STRIDE);
    framebuffer->width = width;
    framebuffer->height = height;
    assert(framebuffer != NULL);
    assert(framebuffer->buffer != NULL);
}

void destroy_framebuffer(framebuffer_t *framebuffer) {
    assert(framebuffer != NULL);
    assert(framebuffer->buffer != NULL);
    free(framebuffer->buffer);
}

void draw_mesh_framebuffer(framebuffer_t *framebuffer,
                           mesh_t *mesh,
                           mat4_t *model,
                           mat4_t *view,
                           mat4_t *projection) {
    mat4_t mv, mvp;
    mul_mat4(view, model, &mv);
    mul_mat4(projection, &mv, &mvp);

    for (unsigned i = 0; i < mesh->index_count; i += 3) {
        vertex_t *a = mesh->vertices + mesh->indices[i + 0];
        vertex_t *b = mesh->vertices + mesh->indices[i + 1];
        vertex_t *c = mesh->vertices + mesh->indices[i + 2];

        // Convert vertices to clip space
        vec3_t ca, cb, cc;
        local_to_clip(&a->position, &mvp, &ca);
        local_to_clip(&b->position, &mvp, &cb);
        local_to_clip(&c->position, &mvp, &cc);

        // Compute screen space coordinates
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
                                       &c->color);
    }
}

void rasterize_triangle_framebuffer(framebuffer_t *framebuffer,
                                    vec2_t *pa,
                                    vec2_t *pb,
                                    vec2_t *pc,
                                    color_t *ca,
                                    color_t *cb,
                                    color_t *cc) {
    vec2_t position;
    vec3_t barycoord;
    color_t color;
    for (unsigned i = 0; i < framebuffer->width; i++) {
        for (unsigned j = 0; j < framebuffer->height; j++) {
            position.x = i;
            position.y = j;

            compute_barycentric(pa, pb, pc, &position, &barycoord);
            if (barycoord.x >= 0 && barycoord.y >= 0 && barycoord.z >= 0) {
                color.r = ca->r * barycoord.x + cb->r * barycoord.y +
                          cc->r * barycoord.z;
                color.g = ca->g * barycoord.x + cb->g * barycoord.y +
                          cc->g * barycoord.z;
                color.b = ca->b * barycoord.x + cb->b * barycoord.y +
                          cc->b * barycoord.z;
                color.a = ca->a * barycoord.x + cb->a * barycoord.y +
                          cc->a * barycoord.z;
                write_framebuffer(framebuffer, &position, &color);
            }
        }
    }
}

void write_framebuffer(framebuffer_t *framebuffer,
                       vec2_t *position,
                       color_t *color) {
    unsigned row = position->y;
    unsigned col = position->x;
    unsigned offset = row * framebuffer->width + col;
    memcpy(framebuffer->buffer + offset, color, PIXEL_STRIDE);
}

void clear_framebuffer(framebuffer_t *framebuffer, color_t *clear_value) {
    unsigned dimensions = framebuffer->width * framebuffer->height;
    for (unsigned offset = 0; offset < dimensions; offset++) {
        memcpy(framebuffer->buffer + offset, clear_value, PIXEL_STRIDE);
    }
}