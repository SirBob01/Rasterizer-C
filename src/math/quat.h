#ifndef MATH_QUAT_H
#define MATH_QUAT_H

#include "vec3.h"

/**
 * @brief Quaternion.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} quat_t;

/**
 * @brief Create a axis-angle (radians) quaternion.
 *
 * @param axis
 * @param angle
 * @return quat_t
 */
quat_t make_axis_angle_quat(vec3_t axis, float angle);

/**
 * @brief Multiply quaternions.
 *
 * @param a
 * @param b
 * @return quat_t
 */
quat_t multiply_quat(quat_t a, quat_t b);

#endif