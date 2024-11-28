#include "vec4.h"

vec4_t make_vec3_vec4(vec3_t a, float w) {
    vec4_t b;
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    b.w = w;
    return b;
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
