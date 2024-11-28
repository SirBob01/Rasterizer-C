#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdbool.h>

#include "color.h"
#include "math/mat4.h"
#include "mesh.h"
#include "texture.h"

/**
 * @brief Buffer of RGBA color pixels that represents a render target.
 *
 */
typedef struct {
    color_t *color;
    float *depth;
    unsigned width;
    unsigned height;
} framebuffer_t;

/**
 * @brief Create a framebuffer.
 *
 * @param framebuffer
 * @param width
 * @param height
 */
void create_framebuffer(framebuffer_t *framebuffer,
                        unsigned width,
                        unsigned height);

/**
 * @brief Destroy a framebuffer.
 *
 * @param framebuffer
 */
void destroy_framebuffer(framebuffer_t *framebuffer);

/**
 * @brief Draw a mesh to the framebuffer.
 *
 * @param framebuffer
 * @param mesh
 * @param model
 * @param view
 * @param projection
 */
void draw_mesh_framebuffer(framebuffer_t *framebuffer,
                           const mesh_t *mesh,
                           const texture_t *texture,
                           mat4_t model,
                           mat4_t view,
                           mat4_t projection,
                           bool cull_back);

/**
 * @brief Rasterize a triangle.
 *
 * @param framebuffer
 * @param texture
 * @param pos_a
 * @param pos_b
 * @param pos_c
 * @param uv_a
 * @param uv_b
 * @param uv_c
 * @param za
 * @param zb
 * @param zc
 */
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
                                    float zc);

/**
 * @brief Draw a pixel to the framebuffer.
 *
 * @param framebuffer
 * @param position
 * @param color
 * @param depth
 */
void write_framebuffer(framebuffer_t *framebuffer,
                       vec2_t position,
                       color_t color,
                       float depth);

/**
 * @brief Clear the framebuffer.
 *
 * @param framebuffer
 * @param clear_color
 */
void clear_framebuffer(framebuffer_t *framebuffer, color_t clear_color);

#endif