#ifndef MATH_H
#define MATH_H

/**
 * @brief Cartesian position in 2 dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
} vec2_t;

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
 * @brief Compute barycentric coordinates of a triangle
 *
 * @param a
 * @param b
 * @param c
 * @param point
 * @param result
 */
void compute_barycentric(vec2_t *a,
                         vec2_t *b,
                         vec2_t *c,
                         vec2_t *point,
                         vec3_t *result);

#endif