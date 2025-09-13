#include "mesh.h"
#include "glad/glad.h"
#include "../types.h"
#include <stdlib.h>
#include <stdio.h>

struct mesh *mesh_create_quad(void)
{
	struct mesh *quad = (struct mesh *) (malloc(sizeof(struct mesh)));

	if (quad == NULL) {
		perror("malloc");
		exit(1);
	}

	f32 vertices[] = {
	//  x		y		z		u		v
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	// top right
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	// bottom right
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	// bottom left
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f	// top left
	};

	u32 indices[] = {0, 1, 3, 1, 2, 3};

	quad->indexCount = sizeof(indices) / sizeof(indices[0]);

	glGenVertexArrays(1, &quad->vao);
	glGenBuffers(1, &quad->vbo);
	glGenBuffers(1, &quad->ebo);

	// bind VAO to the current session
	glBindVertexArray(quad->vao);

	// vbo automatically gets bound to current bound vertex array
	glBindBuffer(GL_ARRAY_BUFFER, quad->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// bind ebo to use indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW
	);

	// set vertex attribute pointers
	//
	// for the position
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
		(void *)0
	);
	glEnableVertexAttribArray(0);

	// for the texture uv
	glVertexAttribPointer(
		1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
		(void *)(3 * sizeof(float))
	);
	glEnableVertexAttribArray(1);

	// unbind from VAO session
	glBindVertexArray(0);

	return quad;
}

void mesh_destroy(struct mesh *m)
{
	glDeleteBuffers(1, &m->ebo);
	glDeleteBuffers(1, &m->vbo);
	glDeleteVertexArrays(1, &m->vao);
	free(m);
}
