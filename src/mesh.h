#ifndef MESH_H
#define MESH_H

#include "math/vec2.h"
#include "math/vec3.h"

typedef unsigned index_t;

/**
 * @brief 3D Vertex.
 *
 */
typedef struct {
    vec3_t position;
    vec2_t uv;
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
 * @brief Load a mesh from an obj file.
 *
 * @param mesh
 * @param filename
 */
void load_obj_mesh(mesh_t *mesh, const char *filename);

/**
 * @brief Destroy a mesh.
 *
 * @param mesh
 */
void destroy_mesh(mesh_t *mesh);

#endif