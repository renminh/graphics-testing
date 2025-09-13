#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <stb/stb_image.h>

#include "renderer.h"

void render_init(struct renderer *r)
{
	r->draw_wireframe = false;

	r->current_shader = shader_create(
		"res/shaders/default.vert",
		"res/shaders/default.frag"
	);

	r->textures[TEXTURE_PLAYER] = texture_create(
		"res/images/standing-steve.png"
	);


	r->meshes[MESH_QUAD] = mesh_create_quad();
}

void render(struct renderer *r)
{
	// clear render output and depth buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	struct shader *shader = r->current_shader;
	struct mesh *quad = r->meshes[MESH_QUAD];
	// bind for rendering
	shader_use(shader);
	glBindVertexArray(quad->vao);

	// actual render
	shader_uniform_vec4(
		shader, UNIFORM_COLOR,
		(vec4) {1.0, 1.0, 1.0, 1.0}
	);

	glDrawElements(GL_TRIANGLES, quad->indexCount, GL_UNSIGNED_INT, 0);
	// unbind VAO to not mess up anything else
	glBindVertexArray(0);
}

void render_destroy(struct renderer *r)
{
	for (int i = 0; i < MAX_MESHES; i++)
		mesh_destroy(r->meshes[i]);

	for (int i = 0; i < MAX_SHADERS; i++)
		shader_destroy(r->shaders[i]);
}
