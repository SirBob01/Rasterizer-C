#include <math.h>

#include "mat4.h"

mat4_t make_identity_mat4() {
    static const unsigned N = 4;
    mat4_t mat;
    for (unsigned i = 0; i < N; i++) {
        for (unsigned j = 0; j < N; j++) {
            mat.elements[i * N + j] = (i == j);
        }
    }
    return mat;
}

mat4_t make_transform_mat4(vec3_t translate, quat_t rotation, vec3_t scale) {
    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;
    float w = rotation.w;

    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float xx = x * x2;
    float xy = x * y2;
    float xz = x * z2;
    float yy = y * y2;
    float yz = y * z2;
    float zz = z * z2;
    float wx = w * x2;
    float wy = w * y2;
    float wz = w * z2;

    float sx = scale.x;
    float sy = scale.y;
    float sz = scale.z;

    mat4_t mat;
    mat.elements[0] = (1 - (yy + zz)) * sx;
    mat.elements[1] = (xy + wz) * sx;
    mat.elements[2] = (xz - wy) * sx;
    mat.elements[3] = 0;

    mat.elements[4] = (xy - wz) * sy;
    mat.elements[5] = (1 - (xx + zz)) * sy;
    mat.elements[6] = (yz + wx) * sy;
    mat.elements[7] = 0;

    mat.elements[8] = (xz + wy) * sz;
    mat.elements[9] = (yz - wx) * sz;
    mat.elements[10] = (1 - (xx + yy)) * sz;
    mat.elements[11] = 0;

    mat.elements[12] = translate.x;
    mat.elements[13] = translate.y;
    mat.elements[14] = translate.z;
    mat.elements[15] = 1;
    return mat;
}

mat4_t make_view_mat4(vec3_t position, vec3_t forward, vec3_t up) {
    vec3_t z = negate_vec3(forward);
    vec3_t x = normalize_vec3(cross_vec3(up, z));
    vec3_t y = cross_vec3(z, x);

    mat4_t mat;
    mat.elements[0] = x.x;
    mat.elements[1] = y.x;
    mat.elements[2] = z.x;
    mat.elements[3] = 0;

    mat.elements[4] = x.y;
    mat.elements[5] = y.y;
    mat.elements[6] = z.y;
    mat.elements[7] = 0;

    mat.elements[8] = x.z;
    mat.elements[9] = y.z;
    mat.elements[10] = z.z;
    mat.elements[11] = 0;

    mat.elements[12] = -dot_vec3(x, position);
    mat.elements[13] = -dot_vec3(y, position);
    mat.elements[14] = -dot_vec3(z, position);
    mat.elements[15] = 1;
    return mat;
}

mat4_t
make_perspective_mat4(float aspect, float fovy, float znear, float zfar) {
    float f = 1.0 / tan(0.5 * fovy);
    float dz = znear - zfar;

    mat4_t mat;
    mat.elements[0] = f / aspect;
    mat.elements[1] = 0;
    mat.elements[2] = 0;
    mat.elements[3] = 0;

    mat.elements[4] = 0;
    mat.elements[5] = -f;
    mat.elements[6] = 0;
    mat.elements[7] = 0;

    mat.elements[8] = 0;
    mat.elements[9] = 0;
    mat.elements[10] = (zfar + znear) / dz;
    mat.elements[11] = -1;

    mat.elements[12] = 0;
    mat.elements[13] = 0;
    mat.elements[14] = (2 * zfar * znear) / dz;
    mat.elements[15] = 0;
    return mat;
}

mat4_t mul_mat4(mat4_t a, mat4_t b) {
    static const unsigned N = 4;
    mat4_t c;
    for (unsigned i = 0; i < N; i++) {
        for (unsigned j = 0; j < N; j++) {
            float dot = 0;
            for (unsigned c = 0; c < N; c++) {
                dot += a.elements[c * N + j] * b.elements[i * N + c];
            }
            c.elements[i * N + j] = dot;
        }
    }
    return c;
}