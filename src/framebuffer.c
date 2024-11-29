#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "math/utils.h"

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
                           const texture_t *texture,
                           mat4_t model,
                           mat4_t view,
                           mat4_t projection,
                           bool cull_back) {
    mat4_t mv = mul_mat4(view, model);
    mat4_t mvp = mul_mat4(projection, mv);

    // Iterate over each triangle
    for (unsigned i = 0; i < mesh->index_count; i += 3) {
        vertex_t *a = mesh->vertices + mesh->indices[i + 0];
        vertex_t *b = mesh->vertices + mesh->indices[i + 1];
        vertex_t *c = mesh->vertices + mesh->indices[i + 2];

        // Convert model space to clip space
        vec4_t ca = apply_mat4_vec4(make_vec3_vec4(a->position, 1), mvp);
        vec4_t cb = apply_mat4_vec4(make_vec3_vec4(b->position, 1), mvp);
        vec4_t cc = apply_mat4_vec4(make_vec3_vec4(c->position, 1), mvp);

        // Convert clip space to raster space
        vec2_t sa = clip_to_raster(ca, framebuffer->width, framebuffer->height);
        vec2_t sb = clip_to_raster(cb, framebuffer->width, framebuffer->height);
        vec2_t sc = clip_to_raster(cc, framebuffer->width, framebuffer->height);

        // Backface culling
        if (cull_back) {
            vec2_t ab = sub_vec2(sb, sa);
            vec2_t ac = sub_vec2(sc, sa);
            if (cross_vec2(ab, ac) >= 0) {
                continue;
            }
        }

        // Rasterize
        rasterize_triangle_framebuffer(framebuffer,
                                       texture,
                                       sa,
                                       sb,
                                       sc,
                                       a->uv,
                                       b->uv,
                                       c->uv,
                                       ca.z,
                                       cb.z,
                                       cc.z);
    }
}

void rasterize_triangle_framebuffer(framebuffer_t *framebuffer,
                                    const texture_t *texture,
                                    vec2_t pos_a,
                                    vec2_t pos_b,
                                    vec2_t pos_c,
                                    vec2_t uv_a,
                                    vec2_t uv_b,
                                    vec2_t uv_c,
                                    float za,
                                    float zb,
                                    float zc) {
    // Compute bounding rect of triangle
    unsigned minx = max(min(min(pos_a.x, pos_b.x), pos_c.x), 0);
    unsigned miny = max(min(min(pos_a.y, pos_b.y), pos_c.y), 0);
    unsigned maxx = min(max(max(pos_a.x + 1, pos_b.x + 1), pos_c.x + 1),
                        framebuffer->width - 1);
    unsigned maxy = min(max(max(pos_a.y + 1, pos_b.y + 1), pos_c.y + 1),
                        framebuffer->width - 1);

    // Precompute barycentric scratch values
    vec2_t ab = sub_vec2(pos_b, pos_a);
    vec2_t ac = sub_vec2(pos_c, pos_a);
    float inv_area = 1 / cross_vec2(ab, ac);

    // Scan each pixel in the bounding box
    for (unsigned i = minx; i <= maxx; i++) {
        for (unsigned j = miny; j <= maxy; j++) {
            vec2_t point = {i, j};

            // Compute per pixel barycentric coordinates
            vec2_t ap = sub_vec2(point, pos_a);
            float w1 = cross_vec2(ap, ac) * inv_area;
            float w2 = cross_vec2(ab, ap) * inv_area;
            float w0 = 1 - w1 - w2;

            // Skip out of bounds pixels
            if (w0 < 0 || w1 < 0 || w2 < 0) {
                continue;
            }

            // Interpolate perspective-correct z and uv coordinates
            float inv_za = 1 / za;
            float inv_zb = 1 / zb;
            float inv_zc = 1 / zc;
            float z = 1 / (w0 * inv_za + w1 * inv_zb + w2 * inv_zc);
            float u = z * ((uv_a.x * inv_za) * w0 + (uv_b.x * inv_zb) * w1 +
                           (uv_c.x * inv_zc) * w2);
            float v = z * ((uv_a.y * inv_za) * w0 + (uv_b.y * inv_zb) * w1 +
                           (uv_c.y * inv_zc) * w2);

            // Calculate texture buffer offset
            unsigned tx = u * texture->width;
            unsigned ty = v * texture->height;
            unsigned texture_offset = (ty * texture->width + tx) * 4;

            // Build color
            color_t color = {
                .r = texture->colors[texture_offset + 0],
                .g = texture->colors[texture_offset + 1],
                .b = texture->colors[texture_offset + 2],
                .a = texture->colors[texture_offset + 3],
            };

            // Depth culling
            unsigned framebuffer_offset = j * framebuffer->width + i;
            if (z < framebuffer->depth[framebuffer_offset]) {
                write_framebuffer(framebuffer, point, color, z);
            }
        }
    }
}

void write_framebuffer(framebuffer_t *framebuffer,
                       vec2_t position,
                       color_t color,
                       float depth) {
    unsigned row = position.y;
    unsigned col = position.x;
    unsigned offset = row * framebuffer->width + col;
    memcpy(framebuffer->color + offset, &color, sizeof(color_t));
    framebuffer->depth[offset] = depth;
}

void clear_framebuffer(framebuffer_t *framebuffer, color_t clear_color) {
    unsigned dimensions = framebuffer->width * framebuffer->height;
    for (unsigned offset = 0; offset < dimensions; offset++) {
        memcpy(framebuffer->color + offset, &clear_color, sizeof(color_t));
        framebuffer->depth[offset] = FLT_MAX;
    }
}