#include <math.h>

#include "vec3.h"

vec3_t add_vec3(vec3_t a, vec3_t b) {
    vec3_t c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}

vec3_t sub_vec3(vec3_t a, vec3_t b) {
    vec3_t c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

vec3_t scale_vec3(vec3_t a, float scale) {
    vec3_t b;
    b.x = a.x * scale;
    b.y = a.y * scale;
    b.z = a.z * scale;
    return b;
}

vec3_t negate_vec3(vec3_t a) {
    vec3_t b;
    b.x = -a.x;
    b.y = -a.y;
    b.z = -a.z;
    return b;
}

vec3_t normalize_vec3(vec3_t a) {
    float length_sq = dot_vec3(a, a);
    float inv_length = 1.0 / sqrt(length_sq);
    return scale_vec3(a, inv_length);
}

vec3_t cross_vec3(vec3_t a, vec3_t b) {
    vec3_t c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

float dot_vec3(vec3_t a, vec3_t b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
