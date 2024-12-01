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
 * @brief Remove the w component from a 4-dimensional vector.
 *
 * @param a
 * @return vec3_t
 */
vec3_t make_vec4_vec3(vec4_t a);

/**
 * @brief Compute the sum of vectors.
 *
 * @param a
 * @param b
 * @return vec4_t
 */
vec4_t add_vec4(vec4_t a, vec4_t b);

/**
 * @brief Compute the difference of vectors.
 *
 * @param a
 * @param b
 * @return vec4_t
 */
vec4_t sub_vec4(vec4_t a, vec4_t b);

/**
 * @brief Multiply a vector by a scalar.
 *
 * @param a
 * @param scale
 * @return vec4_t
 */
vec4_t scale_vec4(vec4_t a, float scale);

/**
 * @brief Negate a vector.
 *
 * @param a
 */
vec4_t negate_vec4(vec4_t a);

/**
 * @brief Normalize a vector.
 *
 * @param a
 * @return vec4_t
 */
vec4_t normalize_vec4(vec4_t a);

/**
 * @brief Compute the dot product of vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float dot_vec4(vec4_t a, vec4_t b);

/**
 * @brief Apply a 4x4 matrix to a vector.
 *
 * @param a
 * @param matrix
 * @return vec4_t
 */
vec4_t apply_mat4_vec4(vec4_t a, mat4_t matrix);

#endif