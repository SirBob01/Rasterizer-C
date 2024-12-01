#include <math.h>

#include "vec4.h"

vec4_t make_vec3_vec4(vec3_t a, float w) {
    vec4_t b;
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    b.w = w;
    return b;
}

vec3_t make_vec4_vec3(vec4_t a) {
    vec3_t b;
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    return b;
}

vec4_t add_vec4(vec4_t a, vec4_t b) {
    vec4_t c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    c.w = a.w + b.w;
    return c;
}

vec4_t sub_vec4(vec4_t a, vec4_t b) {
    vec4_t c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    c.w = a.w - b.w;
    return c;
}

vec4_t scale_vec4(vec4_t a, float scale) {
    vec4_t b;
    b.x = a.x * scale;
    b.y = a.y * scale;
    b.z = a.z * scale;
    b.w = a.w * scale;
    return b;
}

vec4_t negate_vec4(vec4_t a) {
    vec4_t b;
    b.x = -a.x;
    b.y = -a.y;
    b.z = -a.z;
    b.w = -a.w;
    return b;
}

vec4_t normalize_vec4(vec4_t a) {
    float length_sq = dot_vec4(a, a);
    float inv_length = 1.0 / sqrt(length_sq);
    return scale_vec4(a, inv_length);
}

float dot_vec4(vec4_t a, vec4_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

vec4_t apply_mat4_vec4(vec4_t a, mat4_t matrix) {
    vec4_t b;

    b.x = matrix.elements[0] * a.x + matrix.elements[4] * a.y +
          matrix.elements[8] * a.z + matrix.elements[12] * a.w;

    b.y = matrix.elements[1] * a.x + matrix.elements[5] * a.y +
          matrix.elements[9] * a.z + matrix.elements[13] * a.w;

    b.z = matrix.elements[2] * a.x + matrix.elements[6] * a.y +
          matrix.elements[10] * a.z + matrix.elements[14] * a.w;

    b.w = matrix.elements[3] * a.x + matrix.elements[7] * a.y +
          matrix.elements[11] * a.z + matrix.elements[15] * a.w;

    return b;
}
