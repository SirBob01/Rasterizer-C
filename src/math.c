#include <math.h>

#include "./math.h"

float min(float a, float b) { return a < b ? a : b; }

float max(float a, float b) { return a > b ? a : b; }

float dot_vec2(const vec2_t *a, const vec2_t *b) {
    return a->x * b->x + a->y * b->y;
}

float dot_vec3(const vec3_t *a, const vec3_t *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void cross_vec3(const vec3_t *a, const vec3_t *b, vec3_t *c) {
    c->x = a->y * b->z - a->z * b->y;
    c->y = a->z * b->x - a->x * b->z;
    c->z = a->x * b->y - a->y * b->x;
}

void negate_vec3(vec3_t *a) {
    a->x *= -1;
    a->y *= -1;
    a->z *= -1;
}

void normalize_vec3(vec3_t *a) {
    float inv_length = 1.0 / sqrt(dot_vec3(a, a));
    a->x *= inv_length;
    a->y *= inv_length;
    a->z *= inv_length;
}

void compute_barycentric(const vec2_t *a,
                         const vec2_t *b,
                         const vec2_t *c,
                         const vec2_t *point,
                         vec3_t *result) {
    vec2_t ab = {
        .x = b->x - a->x,
        .y = b->y - a->y,
    };
    vec2_t ac = {
        .x = c->x - a->x,
        .y = c->y - a->y,
    };
    vec2_t ap = {
        .x = point->x - a->x,
        .y = point->y - a->y,
    };

    float d00 = dot_vec2(&ab, &ab);
    float d01 = dot_vec2(&ab, &ac);
    float d11 = dot_vec2(&ac, &ac);
    float d20 = dot_vec2(&ap, &ab);
    float d21 = dot_vec2(&ap, &ac);
    float inv = 1.0 / (d00 * d11 - d01 * d01);

    result->y = (d11 * d20 - d01 * d21) * inv;
    result->z = (d00 * d21 - d01 * d20) * inv;
    result->x = 1.0 - (result->y + result->z);
}

void make_axis_angle_quat(quat_t *quat, const vec3_t *axis, float angle) {
    float half_angle = 0.5 * angle;
    float sine = sin(half_angle);
    quat->x = axis->x * sine;
    quat->y = axis->y * sine;
    quat->z = axis->z * sine;
    quat->w = cos(half_angle);
}

void make_identity_mat4(mat4_t *mat) {
    static const unsigned N = 4;
    for (unsigned i = 0; i < N; i++) {
        for (unsigned j = 0; j < N; j++) {
            mat->elements[i * N + j] = (i == j);
        }
    }
}

void make_transform_mat4(mat4_t *mat,
                         const vec3_t *position,
                         const quat_t *rotation,
                         const vec3_t *scale) {
    float x = rotation->x;
    float y = rotation->y;
    float z = rotation->z;
    float w = rotation->w;

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

    float sx = scale->x;
    float sy = scale->y;
    float sz = scale->z;

    mat->elements[0] = (1 - (yy + zz)) * sx;
    mat->elements[1] = (xy + wz) * sx;
    mat->elements[2] = (xz - wy) * sx;
    mat->elements[3] = 0;

    mat->elements[4] = (xy - wz) * sy;
    mat->elements[5] = (1 - (xx + zz)) * sy;
    mat->elements[6] = (yz + wx) * sy;
    mat->elements[7] = 0;

    mat->elements[8] = (xz + wy) * sz;
    mat->elements[9] = (yz - wx) * sz;
    mat->elements[10] = (1 - (xx + yy)) * sz;
    mat->elements[11] = 0;

    mat->elements[12] = position->x;
    mat->elements[13] = position->y;
    mat->elements[14] = position->z;
    mat->elements[15] = 1;
}

void make_view_mat4(mat4_t *mat,
                    const vec3_t *position,
                    const vec3_t *forward,
                    const vec3_t *up) {
    vec3_t z = *forward;
    negate_vec3(&z);

    vec3_t x;
    cross_vec3(up, &z, &x);
    normalize_vec3(&x);

    vec3_t y;
    cross_vec3(&z, &x, &y);

    mat->elements[0] = x.x;
    mat->elements[1] = y.x;
    mat->elements[2] = z.x;
    mat->elements[3] = 0;

    mat->elements[4] = x.y;
    mat->elements[5] = y.y;
    mat->elements[6] = z.y;
    mat->elements[7] = 0;

    mat->elements[8] = x.z;
    mat->elements[9] = y.z;
    mat->elements[10] = z.z;
    mat->elements[11] = 0;

    mat->elements[12] = -dot_vec3(&x, position);
    mat->elements[13] = -dot_vec3(&y, position);
    mat->elements[14] = -dot_vec3(&z, position);
    mat->elements[15] = 1;
}

void make_perspective_mat4(mat4_t *mat,
                           float aspect,
                           float fovy,
                           float znear,
                           float zfar) {
    float f = 1.0 / tan(0.5 * fovy);
    float dz = znear - zfar;

    mat->elements[0] = f / aspect;
    mat->elements[1] = 0;
    mat->elements[2] = 0;
    mat->elements[3] = 0;

    mat->elements[4] = 0;
    mat->elements[5] = -f;
    mat->elements[6] = 0;
    mat->elements[7] = 0;

    mat->elements[8] = 0;
    mat->elements[9] = 0;
    mat->elements[10] = (zfar + znear) / dz;
    mat->elements[11] = -1;

    mat->elements[12] = 0;
    mat->elements[13] = 0;
    mat->elements[14] = (2 * zfar * znear) / dz;
    mat->elements[15] = 0;
}

void mul_mat4(const mat4_t *a, const mat4_t *b, mat4_t *c) {
    static const unsigned N = 4;
    for (unsigned i = 0; i < N; i++) {
        for (unsigned j = 0; j < N; j++) {
            float dot = 0;
            for (unsigned c = 0; c < N; c++) {
                dot += a->elements[c * N + j] * b->elements[i * N + c];
            }
            c->elements[i * N + j] = dot;
        }
    }
}

void apply_mat4(const vec4_t *point, const mat4_t *transform, vec4_t *result) {
    result->x =
        transform->elements[0] * point->x + transform->elements[4] * point->y +
        transform->elements[8] * point->z + transform->elements[12] * point->w;

    result->y =
        transform->elements[1] * point->x + transform->elements[5] * point->y +
        transform->elements[9] * point->z + transform->elements[13] * point->w;

    result->z =
        transform->elements[2] * point->x + transform->elements[6] * point->y +
        transform->elements[10] * point->z + transform->elements[14] * point->w;

    result->w =
        transform->elements[3] * point->x + transform->elements[7] * point->y +
        transform->elements[11] * point->z + transform->elements[15] * point->w;
}

void local_to_clip(const vec3_t *position, const mat4_t *mvp, vec4_t *result) {
    vec4_t v4 = {
        .x = position->x,
        .y = position->y,
        .z = position->z,
        .w = 1,
    };
    apply_mat4(&v4, mvp, result);
}

void clip_to_screen(const vec4_t *clip,
                    unsigned width,
                    unsigned height,
                    vec2_t *result) {
    float inv_w = 1.0 / clip->w;
    float ndc_x = clip->x * inv_w;
    float ndc_y = clip->y * inv_w;
    result->x = width * ((ndc_x + 1.0) * 0.5);
    result->y = height * ((ndc_y + 1.0) * 0.5);
}

float degrees_to_radians(float v) { return v * M_PI / 180.0; }