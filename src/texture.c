#define STB_IMAGE_IMPLEMENTATION

#include <assert.h>
#include <stb_image.h>

#include "texture.h"

void load_texture(texture_t *texture, const char *filename) {
    assert(texture != NULL);
    int w, h, c;
    texture->colors = stbi_load(filename, &w, &h, &c, 4);
    texture->width = w;
    texture->height = h;
    assert(texture->colors != NULL);
}

void destroy_texture(texture_t *texture) {
    assert(texture != NULL);
    assert(texture->colors != NULL);
    stbi_image_free(texture->colors);
}
