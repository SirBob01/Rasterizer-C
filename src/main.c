#include <SDL3/SDL_keycode.h>
#include <math.h>

#include "display.h"
#include "framebuffer.h"
#include "input.h"
#include "math/utils.h"
#include "mesh.h"

static const float LOGICAL_WIDTH = 640;
static const float LOGICAL_HEIGHT = 480;

int main() {
    // Create the framebuffer
    framebuffer_t framebuffer;
    create_framebuffer(&framebuffer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

    // Create the mesh
    mesh_t mesh;
    load_obj_mesh(&mesh, "../assets/viking_room.obj");

    // Create the texture
    texture_t texture;
    load_texture(&texture, "../assets/viking_room.png");

    // Initialize display
    display_t display;
    create_display(&display, LOGICAL_WIDTH, LOGICAL_HEIGHT, "Rasterizer-C");

    // Initialize input handler
    input_t input;
    create_input(&input);

    // Clear value
    color_t clear_color = {
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 255,
    };

    // Camera vectors
    vec3_t eye = {2, 2, 2};
    vec3_t up = {0, 1, 0};
    vec3_t forward = {-2, -2, -2};
    forward = normalize_vec3(forward);

    // Coordinate space matrices
    float aspect = (float)framebuffer.width / framebuffer.height;
    float fovy = degrees_to_radians(45.0);
    mat4_t projection = make_perspective_mat4(aspect, fovy, 0.1, 10000);

    // Model orientation correction rotation
    vec3_t rotation_axis = {1, 0, 0};
    quat_t correction_rotation = make_axis_angle_quat(rotation_axis, -M_PI_2);

    // Main loop
    float speed = 0.01;
    float timer = 0;
    while (!input.quit) {
        poll_input(&input);

        if (is_keydown_input(&input, SDLK_W)) {
            eye = add_vec3(eye, scale_vec3(forward, speed));
        }
        if (is_keydown_input(&input, SDLK_S)) {
            eye = sub_vec3(eye, scale_vec3(forward, speed));
        }
        if (is_keydown_input(&input, SDLK_Q)) {
            eye = add_vec3(eye, scale_vec3(up, speed));
        }
        if (is_keydown_input(&input, SDLK_E)) {
            eye = sub_vec3(eye, scale_vec3(up, speed));
        }

        vec3_t right = cross_vec3(forward, up);
        if (is_keydown_input(&input, SDLK_D)) {
            eye = add_vec3(eye, scale_vec3(right, speed));
        }
        if (is_keydown_input(&input, SDLK_A)) {
            eye = sub_vec3(eye, scale_vec3(right, speed));
        }

        mat4_t view = make_view_mat4(eye, forward, up);

        vec3_t position = {0, 0, 0};
        vec3_t scale = {1, 1, 1};
        vec3_t rotation_axis = {0, 1, 0};
        quat_t rotation =
            multiply_quat(make_axis_angle_quat(rotation_axis, -timer - M_PI_2),
                          correction_rotation);
        mat4_t model = make_transform_mat4(position, rotation, scale);

        draw_mesh_framebuffer(&framebuffer,
                              &mesh,
                              &texture,
                              model,
                              view,
                              projection,
                              true);

        refresh_display(&display, &framebuffer);
        clear_framebuffer(&framebuffer, clear_color);

        timer += 0.001;
    }

    // Cleanup
    destroy_texture(&texture);
    destroy_mesh(&mesh);
    destroy_input(&input);
    destroy_display(&display);
    destroy_framebuffer(&framebuffer);
    return 0;
}