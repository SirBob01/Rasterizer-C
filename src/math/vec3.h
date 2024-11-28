#ifndef MATH_VEC3_H
#define MATH_VEC3_H

/**
 * @brief Cartesian position in 3-dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

/**
 * @brief Compute the sum of vectors.
 *
 * @param a
 * @param b
 * @return vec3_t
 */
vec3_t add_vec3(vec3_t a, vec3_t b);

/**
 * @brief Compute the difference of vectors.
 *
 * @param a
 * @param b
 * @return vec3_t
 */
vec3_t sub_vec3(vec3_t a, vec3_t b);

/**
 * @brief Multiply a vector by a scalar.
 *
 * @param a
 * @param scale
 * @return vec3_t
 */
vec3_t scale_vec3(vec3_t a, float scale);

/**
 * @brief Negate a vector.
 *
 * @param a
 */
vec3_t negate_vec3(vec3_t a);

/**
 * @brief Normalize a vector.
 *
 * @param a
 * @return vec3_t
 */
vec3_t normalize_vec3(vec3_t a);

/**
 * @brief Compute the cross product of vectors.
 *
 * @param a
 * @param b
 * @return vec3_t
 */
vec3_t cross_vec3(vec3_t a, vec3_t b);

/**
 * @brief Compute the dot product of vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float dot_vec3(vec3_t a, vec3_t b);

#endif