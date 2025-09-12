#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>

#include "renderer.h"
#include "../types.h"
#include "../shader/shader.h"

void render_init(struct renderer *r)
{
	r->draw_wireframe = false;

	r->default_shader = shader_create(
		"res/shaders/default.vert",
		"res/shaders/default.frag"
	);
}

void quad_init(struct renderer *r)
{
	/*
	 * vertex shader works as such
	 * create memory on the GPU where we store vertex data, then we configure
	 * how OpenGL should interpret this memory and specify the data we'll send
	 * to the GPU. Then the Vertex shader processes as much vertices as we tells
	 * them from memory
	 */
	 f32 vertices[] = {
		0.5, 0.5, 0.0,		// top right
		0.5, -0.5, 0.0,		// bottom right
		-0.5, -0.5, 0.0,	// bottom left
		-0.5, 0.5, 0.0,		// top left
		
	};

	u32 indices[] = {
		0, 1, 3,
		1, 2, 3

	};

	glGenVertexArrays(1, &r->vao);
	glGenBuffers(1, &r->vbo);
	glGenBuffers(1, &r->ebo);

	// bind attributes to vao
	glBindVertexArray(r->vao);

	// VBO
	// VBO gets automatically bound to VAO
	glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO's type is GL_ELEMENT_ARRAY_BUFFFER
	// EBO gets automatically bound to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW
	);

// set vertex attributes pointers
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0
	);
	glEnableVertexAttribArray(0);
}


void quad_draw(struct renderer *r)
{
	// i'll pass in some vertices in here to generate my own quad
}

void render(struct renderer *r)
{

	// clear render output and depth buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind for rendering
	shader_use(r->default_shader);

	// actual render
	glUniform4f(r->default_shader->uniforms[U_COLOR], 1.0f, 1.0f, 1.0f, 1.0f);

	glBindVertexArray(r->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// unbind VAO to not mess up anything else
	glBindVertexArray(0);
}

void render_destroy(struct renderer *r)
{
	shader_destroy(r->default_shader);
	glDeleteBuffers(1, &r->vbo);
	glDeleteBuffers(1, &r->ebo);
	glDeleteVertexArrays(1, &r->vao);
}
