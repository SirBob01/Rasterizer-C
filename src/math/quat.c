#include <math.h>

#include "quat.h"

quat_t make_axis_angle_quat(vec3_t axis, float angle) {
    float half_angle = 0.5 * angle;
    float sine = sin(half_angle);
    quat_t quat;
    quat.x = axis.x * sine;
    quat.y = axis.y * sine;
    quat.z = axis.z * sine;
    quat.w = cos(half_angle);
    return quat;
}

quat_t multiply_quat(quat_t a, quat_t b) {
    quat_t c;
    c.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    c.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    c.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    c.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    return c;
}
