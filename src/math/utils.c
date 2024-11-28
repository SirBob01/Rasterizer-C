
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
