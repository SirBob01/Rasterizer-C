#include <SDL3/SDL_pixels.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"

void create_display(display_t *display,
                    unsigned width,
                    unsigned height,
                    const char *title) {
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    display->window = SDL_CreateWindow(title, 640, 480, SDL_WINDOW_RESIZABLE);
    if (!display->window) {
        fprintf(stderr,
                "Error: Unable to initialize window (%s)\n",
                SDL_GetError());
        exit(1);
    }

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if (!display->renderer) {
        fprintf(stderr,
                "Error: Unable to initialize display (%s)\n",
                SDL_GetError());
        exit(1);
    }

    display->texture = SDL_CreateTexture(display->renderer,
                                         SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         width,
                                         height);
    if (!display->texture) {
        fprintf(stderr,
                "Error: Unable to initialize texture (%s)\n",
                SDL_GetError());
        exit(1);
    }

    // Set the logical presentation of the display
    SDL_SetRenderLogicalPresentation(display->renderer,
                                     width,
                                     height,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Set the scale mode of the display texture
    SDL_SetTextureScaleMode(display->texture, SDL_SCALEMODE_NEAREST);
}

void destroy_display(display_t *display) {
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
}

void refresh_display(display_t *display, framebuffer_t *framebuffer) {
    // Update the texture
    SDL_UpdateTexture(display->texture,
                      NULL,
                      framebuffer->color,
                      framebuffer->width * sizeof(color_t));

    // Render the texture
    SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_NONE);
    SDL_RenderTexture(display->renderer, display->texture, NULL, NULL);

    // Present and clear
    SDL_RenderPresent(display->renderer);
}
