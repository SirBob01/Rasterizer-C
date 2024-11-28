#ifndef MATH_VEC2_H
#define MATH_VEC2_H

/**
 * @brief Cartesian position in 2-dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
} vec2_t;

/**
 * @brief Compute the sum of vectors.
 *
 * @param a
 * @param b
 * @return vec2_t
 */
vec2_t add_vec2(vec2_t a, vec2_t b);

/**
 * @brief Compute the difference of vectors.
 *
 * @param a
 * @param b
 * @return vec2_t
 */
vec2_t sub_vec2(vec2_t a, vec2_t b);

/**
 * @brief Multiply a vector by a scalar.
 *
 * @param a
 * @param scale
 * @return vec2_t
 */
vec2_t scale_vec2(vec2_t a, float scale);

/**
 * @brief Negate a vector.
 *
 * @param a
 */
vec2_t negate_vec2(vec2_t a);

/**
 * @brief Normalize a vector.
 *
 * @param a
 * @return vec2_t
 */
vec2_t normalize_vec2(vec2_t a);

/**
 * @brief Compute the cross product of vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float cross_vec2(vec2_t a, vec2_t b);

/**
 * @brief Compute the dot product of vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float dot_vec2(vec2_t a, vec2_t b);

#endif