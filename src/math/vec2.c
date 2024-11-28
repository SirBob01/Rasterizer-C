#include <math.h>

#include "vec2.h"

vec2_t add_vec2(vec2_t a, vec2_t b) {
    vec2_t c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

vec2_t sub_vec2(vec2_t a, vec2_t b) {
    vec2_t c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

vec2_t scale_vec2(vec2_t a, float scale) {
    vec2_t b;
    b.x = a.x * scale;
    b.y = a.y * scale;
    return b;
}

vec2_t negate_vec2(vec2_t a) {
    vec2_t b;
    b.x = -a.x;
    b.y = -a.y;
    return b;
}

vec2_t normalize_vec2(vec2_t a) {
    float length_sq = dot_vec2(a, a);
    float inv_length = 1.0 / sqrt(length_sq);
    return scale_vec2(a, inv_length);
}

float dot_vec2(vec2_t a, vec2_t b) { return a.x * b.x + a.y * b.y; }
