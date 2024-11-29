#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL3/SDL.h>

#include "framebuffer.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    float width;
    float height;
} display_t;

/**
 * @brief Create a display.
 *
 * @param display Target display.
 * @param width   Logical width of the display.
 * @param height  Logical height of the display.
 * @param title   Title of the window.
 */
void create_display(display_t *display,
                    unsigned width,
                    unsigned height,
                    const char *title);

/**
 * @brief Destroy a display.
 *
 * @param display
 */
void destroy_display(display_t *display);

/**
 * @brief Set the title of the display.
 *
 * @param display
 * @param title
 */
void set_title_display(display_t *display, const char *title);

/**
 * @brief Render a framebuffer onto the display.
 *
 * @param display
 * @param framebuffer
 */
void refresh_display(display_t *display, framebuffer_t *framebuffer);

#endif