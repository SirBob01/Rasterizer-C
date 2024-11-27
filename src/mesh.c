#include <assert.h>
#include <stdlib.h>

#include "mesh.h"

void create_mesh(mesh_t *mesh, unsigned vertex_count, unsigned index_count) {
    assert(mesh != NULL);
    mesh->vertices = malloc(vertex_count * sizeof(vertex_t));
    mesh->vertex_count = vertex_count;

    mesh->indices = malloc(index_count * sizeof(index_t));
    mesh->index_count = index_count;
    assert(mesh->vertices != NULL);
    assert(mesh->indices != NULL);
}

void destroy_mesh(mesh_t *mesh) {
    assert(mesh != NULL);
    assert(mesh->vertices != NULL);
    assert(mesh->indices != NULL);
    free(mesh->vertices);
    free(mesh->indices);
}