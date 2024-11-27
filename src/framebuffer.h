#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "color.h"
#include "math.h"
#include "mesh.h"

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
                           const mat4_t *model,
                           const mat4_t *view,
                           const mat4_t *projection);

/**
 * @brief Rasterize a triangle.
 *
 * @param framebuffer
 * @param a A position
 * @param b B position
 * @param c C position
 * @param ca A color
 * @param cb B color
 * @param cc C color
 * @param da A depth
 * @param db B depth
 * @param dc C depth
 */
void rasterize_triangle_framebuffer(framebuffer_t *framebuffer,
                                    const vec2_t *a,
                                    const vec2_t *b,
                                    const vec2_t *c,
                                    const color_t *ca,
                                    const color_t *cb,
                                    const color_t *cc,
                                    float da,
                                    float db,
                                    float dc);

/**
 * @brief Draw a pixel to the framebuffer.
 *
 * @param framebuffer
 * @param position
 * @param color
 * @param depth
 */
void write_framebuffer(framebuffer_t *framebuffer,
                       const vec2_t *position,
                       const color_t *color,
                       float depth);

/**
 * @brief Clear the framebuffer.
 *
 * @param framebuffer
 * @param clear_value
 */
void clear_framebuffer(framebuffer_t *framebuffer, const color_t *clear_value);

#endif