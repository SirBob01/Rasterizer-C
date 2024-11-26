#ifndef COLOR_H
#define COLOR_H

/**
 * @brief RGBA color value.
 *
 */
typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char g;
    unsigned char r;
} color_t;

/**
 * @brief Stride length of a pixel.
 *
 */
static const unsigned PIXEL_STRIDE = sizeof(color_t);

#endif