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
    color_t *buffer;
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
                           mesh_t *mesh,
                           mat4_t *model,
                           mat4_t *view,
                           mat4_t *projection);

/**
 * @brief Rasterize a triangle.
 *
 * @param framebuffer
 * @param pa
 * @param pb
 * @param pc
 * @param ca
 * @param cb
 * @param cc
 */
void rasterize_triangle_framebuffer(framebuffer_t *framebuffer,
                                    vec2_t *pa,
                                    vec2_t *pb,
                                    vec2_t *pc,
                                    color_t *ca,
                                    color_t *cb,
                                    color_t *cc);

/**
 * @brief Draw a pixel to the framebuffer.
 *
 * @param framebuffer
 * @param position
 * @param color
 */
void write_framebuffer(framebuffer_t *framebuffer,
                       vec2_t *position,
                       color_t *color);

/**
 * @brief Clear the framebuffer.
 *
 * @param framebuffer
 * @param clear_value
 */
void clear_framebuffer(framebuffer_t *framebuffer, color_t *clear_value);

#endif