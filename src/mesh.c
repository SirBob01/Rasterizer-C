#include <stdlib.h>

#include "mesh.h"

void create_mesh(mesh_t *mesh, unsigned vertex_count, unsigned index_count) {
    mesh->vertices = malloc(vertex_count * sizeof(vertex_t));
    mesh->vertex_count = vertex_count;

    mesh->indices = malloc(index_count * sizeof(index_t));
    mesh->index_count = index_count;
}

void destroy_mesh(mesh_t *mesh) {
    free(mesh->vertices);
    free(mesh->indices);
}