#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include <tinyobj_loader_c.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mesh.h"

typedef struct {
    char *buffer;
    unsigned size;
} obj_ptr_t;

void create_mesh(mesh_t *mesh, unsigned vertex_count, unsigned index_count) {
    assert(mesh != NULL);
    mesh->vertices = malloc(vertex_count * sizeof(vertex_t));
    mesh->vertex_count = vertex_count;

    mesh->indices = malloc(index_count * sizeof(index_t));
    mesh->index_count = index_count;
    assert(mesh->vertices != NULL);
    assert(mesh->indices != NULL);
}

static void get_file_data(void *ctx,
                          const char *filename,
                          const int is_mtl,
                          const char *obj_filename,
                          char **data,
                          size_t *len) {
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);

    obj_ptr_t *obj_ptr = ctx;
    unsigned capacity = 1;
    obj_ptr->buffer = malloc(capacity);
    obj_ptr->size = 0;

    char c;
    while ((c = getc(fp)) != EOF) {
        if (obj_ptr->size >= capacity) {
            capacity *= 2;
            obj_ptr->buffer = realloc(obj_ptr->buffer, capacity);
        }
        obj_ptr->buffer[obj_ptr->size++] = c;
    }
    fclose(fp);

    *data = obj_ptr->buffer;
    *len = obj_ptr->size;
}

void load_obj_mesh(mesh_t *mesh, const char *filename) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t *shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t *materials = NULL;
    size_t num_materials;

    obj_ptr_t ctx;
    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
    int ret = tinyobj_parse_obj(&attrib,
                                &shapes,
                                &num_shapes,
                                &materials,
                                &num_materials,
                                filename,
                                get_file_data,
                                &ctx,
                                flags);
    assert(ret == TINYOBJ_SUCCESS);

    mesh->vertex_count = attrib.num_face_num_verts * 3;
    mesh->vertices = malloc(mesh->vertex_count * sizeof(vertex_t));

    mesh->index_count = attrib.num_face_num_verts * 3;
    mesh->indices = malloc(mesh->index_count * sizeof(index_t));

    // Load vertices
    unsigned face_offset = 0;
    unsigned vertex_index = 0;
    unsigned index_index = 0;
    for (unsigned i = 0; i < attrib.num_face_num_verts; i++) {
        for (unsigned f = 0; f < attrib.face_num_verts[i] / 3; f++) {
            tinyobj_vertex_index_t i0 = attrib.faces[face_offset + 3 * f + 0];
            tinyobj_vertex_index_t i1 = attrib.faces[face_offset + 3 * f + 1];
            tinyobj_vertex_index_t i2 = attrib.faces[face_offset + 3 * f + 2];

            vertex_t v0;
            vertex_t v1;
            vertex_t v2;

            v0.position.x = attrib.vertices[3 * i0.v_idx + 0];
            v1.position.x = attrib.vertices[3 * i1.v_idx + 0];
            v2.position.x = attrib.vertices[3 * i2.v_idx + 0];

            v0.position.y = attrib.vertices[3 * i0.v_idx + 1];
            v1.position.y = attrib.vertices[3 * i1.v_idx + 1];
            v2.position.y = attrib.vertices[3 * i2.v_idx + 1];

            v0.position.z = attrib.vertices[3 * i0.v_idx + 2];
            v1.position.z = attrib.vertices[3 * i1.v_idx + 2];
            v2.position.z = attrib.vertices[3 * i2.v_idx + 2];

            v0.uv.x = attrib.texcoords[2 * i0.vt_idx + 0];
            v1.uv.x = attrib.texcoords[2 * i1.vt_idx + 0];
            v2.uv.x = attrib.texcoords[2 * i2.vt_idx + 0];

            v0.uv.y = 1 - attrib.texcoords[2 * i0.vt_idx + 1];
            v1.uv.y = 1 - attrib.texcoords[2 * i1.vt_idx + 1];
            v2.uv.y = 1 - attrib.texcoords[2 * i2.vt_idx + 1];

            mesh->vertices[vertex_index++] = v0;
            mesh->vertices[vertex_index++] = v1;
            mesh->vertices[vertex_index++] = v2;

            mesh->indices[index_index + 0] = index_index + 0;
            mesh->indices[index_index + 1] = index_index + 1;
            mesh->indices[index_index + 2] = index_index + 2;
            index_index += 3;
        }
        face_offset += attrib.face_num_verts[i];
    }

    // Clean up the file buffer
    free(ctx.buffer);
}

void destroy_mesh(mesh_t *mesh) {
    assert(mesh != NULL);
    assert(mesh->vertices != NULL);
    assert(mesh->indices != NULL);
    free(mesh->vertices);
    free(mesh->indices);
}