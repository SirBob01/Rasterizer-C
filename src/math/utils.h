#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "vec2.h"
#include "vec4.h"

/**
 * @brief Compute the minimum of two floats.
 *
 * @param a
 * @param b
 * @return float
 */
float min(float a, float b);

/**
 * @brief Compute the maximum of two floats.
 *
 * @param a
 * @param b
 */
float max(float a, float b);

/**
 * @brief Convert degrees to radians
 *
 * @param degrees
 * @return float
 */
float degrees_to_radians(float degrees);

/**
 * @brief Convert radians to degrees
 *
 * @param radians
 * @return float
 */
float radians_to_degrees(float radians);

/**
 * @brief Convert a 3D clip position to raster space
 *
 * @param clip
 * @param width
 * @param height
 * @return vec2_t
 */
vec2_t clip_to_raster(vec4_t clip, unsigned width, unsigned height);

#endif