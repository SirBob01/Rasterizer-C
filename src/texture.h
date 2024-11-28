#ifndef TEXTURE_H
#define TEXTURE_H

/**
 * @brief 2D texture.
 *
 */
typedef struct {
    unsigned char *colors;
    unsigned width;
    unsigned height;
} texture_t;

/**
 * @brief Load a texture from a file.
 *
 * @param texture
 * @param filename
 */
void load_texture(texture_t *texture, const char *filename);

/**
 * @brief Destroy a texture.
 *
 * @param texture
 */
void destroy_texture(texture_t *texture);

#endif