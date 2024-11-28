
#include <math.h>

#include "utils.h"

float min(float a, float b) { return a < b ? a : b; }

float max(float a, float b) { return a > b ? a : b; }

float degrees_to_radians(float degrees) { return degrees * M_PI / 180.0; }

float radians_to_degrees(float radians) { return radians * 180.0 / M_PI; }

vec2_t clip_to_raster(vec4_t clip, unsigned width, unsigned height) {
    float inv_w = 1.0 / clip.w;
    float ndc_x = clip.x * inv_w;
    float ndc_y = clip.y * inv_w;

    vec2_t raster;
    raster.x = width * ((ndc_x + 1.0) * 0.5);
    raster.y = height * ((ndc_y + 1.0) * 0.5);
    return raster;
}

vec3_t barycentric(vec2_t a, vec2_t b, vec2_t c, vec2_t point) {
    vec2_t ab = sub_vec2(b, a);
    vec2_t ac = sub_vec2(c, a);
    vec2_t ap = sub_vec2(point, a);

    float d00 = dot_vec2(ab, ab);
    float d01 = dot_vec2(ab, ac);
    float d11 = dot_vec2(ac, ac);
    float d20 = dot_vec2(ap, ab);
    float d21 = dot_vec2(ap, ac);
    float inv = 1.0 / (d00 * d11 - d01 * d01);

    vec3_t coord;
    coord.y = (d11 * d20 - d01 * d21) * inv;
    coord.z = (d00 * d21 - d01 * d20) * inv;
    coord.x = 1.0 - (coord.y + coord.z);
    return coord;
}