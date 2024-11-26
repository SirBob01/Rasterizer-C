#ifndef MESH_H
#define MESH_H

#include "color.h"
#include "math.h"

typedef unsigned index_t;

/**
 * @brief 3D Vertex.
 *
 */
typedef struct {
    vec3_t position;
    color_t color;
} vertex_t;

/**
 * @brief 3D Mesh.
 *
 */
typedef struct {
    vertex_t *vertices;
    unsigned vertex_count;

    index_t *indices;
    unsigned index_count;
} mesh_t;

/**
 * @brief Create a mesh.
 *
 * @param mesh
 * @param vertex_count
 * @param index_count
 */
void create_mesh(mesh_t *mesh, unsigned vertex_count, unsigned index_count);

/**
 * @brief Destroy a mesh.
 *
 * @param mesh
 */
void destroy_mesh(mesh_t *mesh);

#endif