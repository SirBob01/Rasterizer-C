#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"

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