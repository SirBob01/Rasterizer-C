#include "display.h"
#include "framebuffer.h"
#include "input.h"
#include "math.h"
#include "mesh.h"
#include <math.h>

static const vec3_t GEOM_POSITIONS[4] = {
    {-0.5, 0.0, -0.5},
    {0.5, 0.0, -0.5},
    {0.5, 0.0, 0.5},
    {-0.5, 0.0, 0.5},
};
static const color_t GEOM_COLORS[4] = {
    {.r = 255, .g = 0, .b = 0, .a = 255},
    {.r = 0, .g = 255, .b = 0, .a = 255},
    {.r = 0, .g = 0, .b = 255, .a = 255},
    {.r = 255, .g = 255, .b = 255, .a = 255},
};
static const float LOGICAL_WIDTH = 320;
static const float LOGICAL_HEIGHT = 240;

int main() {
    // Create the framebuffer
    framebuffer_t framebuffer;
    create_framebuffer(&framebuffer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

    // Initialize display
    display_t display;
    create_display(&display, LOGICAL_WIDTH, LOGICAL_HEIGHT, "Rasterizer-C");

    // Initialize input handler
    input_t input;
    create_input(&input);

    // Clear value
    color_t clear_value = {.r = 0, .g = 0, .b = 0, .a = 255};

    // Mesh definition
    mesh_t mesh;
    create_mesh(&mesh, 4, 6);
    for (unsigned i = 0; i < 4; i++) {
        memcpy(&mesh.vertices[i].position, &GEOM_POSITIONS[i], sizeof(vec3_t));
        memcpy(&mesh.vertices[i].color, &GEOM_COLORS[i], sizeof(color_t));
    }
    mesh.indices[0] = 0;
    mesh.indices[1] = 1;
    mesh.indices[2] = 2;
    mesh.indices[3] = 2;
    mesh.indices[4] = 3;
    mesh.indices[5] = 0;

    mat4_t model0, model1, view, projection;
    vec3_t eye = {2, 2, 2};
    vec3_t forward = {-2, -2, -2};
    vec3_t up = {0, 1, 0};
    normalize_vec3(&forward);

    make_identity_mat4(&model0);
    make_identity_mat4(&model1);
    make_view_mat4(&view, &eye, &forward, &up);
    make_perspective_mat4(&projection,
                          (float)framebuffer.width / framebuffer.height,
                          degrees_to_radians(45.0),
                          0.1,
                          10000);

    // Main loop
    float timer = 0;
    while (!input.quit) {
        poll_input(&input);

        vec3_t scale = {1, 1, 1};
        vec3_t rotation_axis = {0, 1, 0};

        vec3_t position0 = {0, 0, 0};
        quat_t rotation0;
        make_axis_angle_quat(&rotation0, &rotation_axis, timer);
        make_transform_mat4(&model0, &position0, &rotation0, &scale);

        vec3_t position1 = {0, sin(timer) * 0.5, 0};
        quat_t rotation1;
        make_axis_angle_quat(&rotation1, &rotation_axis, -timer / 2);
        make_transform_mat4(&model1, &position1, &rotation1, &scale);

        draw_mesh_framebuffer(&framebuffer, &mesh, &model0, &view, &projection);
        draw_mesh_framebuffer(&framebuffer, &mesh, &model1, &view, &projection);

        refresh_display(&display, &framebuffer);
        clear_framebuffer(&framebuffer, &clear_value);

        timer += 0.001;
    }

    // Cleanup
    destroy_mesh(&mesh);
    destroy_input(&input);
    destroy_display(&display);
    destroy_framebuffer(&framebuffer);
    return 0;
}