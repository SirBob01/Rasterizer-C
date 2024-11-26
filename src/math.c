#include "math.h"

float dot_vec2(vec2_t *a, vec2_t *b) { return a->x * b->x + a->y * b->y; }

void compute_barycentric(vec2_t *a,
                         vec2_t *b,
                         vec2_t *c,
                         vec2_t *point,
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

    result->x = (d11 * d20 - d01 * d21) * inv;
    result->y = (d00 * d21 - d01 * d20) * inv;
    result->z = 1.0 - (result->x + result->y);
}