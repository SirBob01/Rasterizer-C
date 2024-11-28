#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "mat4.h"

/**
 * @brief Cartesian position in 4-dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4_t;

/**
 * @brief Add a w component to a 3-dimensional vector.
 *
 * @param a
 * @param w
 * @return vec4_t
 */
vec4_t make_vec3_vec4(vec3_t a, float w);

/**
 * @brief Apply a 4x4 matrix to a vector.
 *
 * @param a
 * @param matrix
 * @return vec4_t
 */
vec4_t apply_mat4_vec4(vec4_t a, mat4_t matrix);

#endif