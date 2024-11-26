#include "display.h"
#include "framebuffer.h"
#include "input.h"

int main() {
    // Create the framebuffer
    framebuffer_t framebuffer;
    create_framebuffer(&framebuffer, 640, 480);

    // Initialize display
    display_t display;
    create_display(&display, 640, 480, "Rasterizer-C");

    // Initialize input handler
    input_t input;
    create_input(&input);

    // Clear value
    color_t clear_value = {.r = 0, .g = 0, .b = 0, .a = 255};

    // Triangle definition
    vec2_t pa = {0, 480};
    vec2_t pb = {320, 0};
    vec2_t pc = {640, 480};
    color_t ca = {.r = 255, .g = 0, .b = 0, .a = 255};
    color_t cb = {.r = 0, .g = 255, .b = 0, .a = 255};
    color_t cc = {.r = 0, .g = 0, .b = 255, .a = 255};

    // Main loop
    while (!input.quit) {
        poll_input(&input);

        rasterize_triangle_framebuffer(&framebuffer,
                                       &pa,
                                       &pb,
                                       &pc,
                                       &ca,
                                       &cb,
                                       &cc);

        refresh_display(&display, &framebuffer);
        clear_framebuffer(&framebuffer, &clear_value);
    }

    // Cleanup
    destroy_input(&input);
    destroy_display(&display);
    destroy_framebuffer(&framebuffer);
    return 0;
}