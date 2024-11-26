#include "display.h"
#include "framebuffer.h"
#include "input.h"
#include "math.h"
#include "mesh.h"

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

    // Mesh definition
    mesh_t mesh;
    create_mesh(&mesh, 3, 3);

    mesh.vertices[0].color.r = 255;
    mesh.vertices[0].color.g = 0;
    mesh.vertices[0].color.b = 0;
    mesh.vertices[0].color.a = 255;

    mesh.vertices[1].color.r = 0;
    mesh.vertices[1].color.g = 255;
    mesh.vertices[1].color.b = 0;
    mesh.vertices[1].color.a = 255;

    mesh.vertices[2].color.r = 0;
    mesh.vertices[2].color.g = 0;
    mesh.vertices[2].color.b = 255;
    mesh.vertices[2].color.a = 255;

    mesh.vertices[0].position.x = 0;
    mesh.vertices[0].position.y = 0;
    mesh.vertices[0].position.z = 0;

    mesh.vertices[1].position.x = 0;
    mesh.vertices[1].position.y = 1;
    mesh.vertices[1].position.z = 0;

    mesh.vertices[2].position.x = 1;
    mesh.vertices[2].position.y = 1;
    mesh.vertices[2].position.z = 0;

    mesh.indices[0] = 0;
    mesh.indices[1] = 1;
    mesh.indices[2] = 2;

    mat4_t model, view, projection;
    vec3_t eye = {2, 2, 2};
    vec3_t forward = {-2, -2, -2};
    vec3_t up = {0, 1, 0};
    make_identity_mat4(&model);
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

        vec3_t position = {0, 0, 0};
        vec3_t scale = {1, 1, 1};
        vec3_t rotation_axis = {0, 1, 0};
        quat_t rotation;
        make_axis_angle_quat(&rotation, &rotation_axis, timer);
        make_transform_mat4(&model, &position, &rotation, &scale);

        draw_mesh_framebuffer(&framebuffer, &mesh, &model, &view, &projection);

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