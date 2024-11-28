#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "quat.h"
#include "vec3.h"

/**
 * @brief 4x4 matrix.
 *
 */
typedef struct {
    float elements[16];
} mat4_t;

/**
 * @brief Make an identity matrix.
 *
 * @return mat4_t
 */
mat4_t make_identity_mat4();

/**
 * @brief Create a transformation matrix.
 *
 * @param translate
 * @param rotation
 * @param scale
 * @return mat4_t
 */
mat4_t make_transform_mat4(vec3_t translate, quat_t rotation, vec3_t scale);

/**
 * @brief Make a view matrix.
 *
 * @param position
 * @param forward
 * @param up
 * @return mat4_t
 */
mat4_t make_view_mat4(vec3_t position, vec3_t forward, vec3_t up);

/**
 * @brief Make a perspective projection matrix. FOV-y must be in radians.
 *
 * @param aspect
 * @param fovy
 * @param znear
 * @param zfar
 * @return mat4_t
 */
mat4_t make_perspective_mat4(float aspect, float fovy, float znear, float zfar);

/**
 * @brief Multiply matrices.
 *
 * @param a
 * @param b
 * @return mat4_t
 */
mat4_t mul_mat4(mat4_t a, mat4_t b);

#endif