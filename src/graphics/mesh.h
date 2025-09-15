#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

typedef enum {
	MESH_QUAD,
	MAX_MESHES
} mesh_type_enum;

struct mesh {
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLsizei index_count;
};

struct mesh mesh_create_quad(void);
void mesh_destroy(struct mesh *m);

#endif
