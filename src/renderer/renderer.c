#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <stb/stb_image.h>
#include <cglm/cam.h>

#include "renderer.h"
#include "../types.h"


void render(struct renderer *r, struct scene *s)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer_use_shader(r, SHADER_DEFAULT);
	shader_uniform_mat4(r->current_shader, UNIFORM_PROJECTION, r->projection);

	shader_uniform_vec4(
		r->current_shader, UNIFORM_COLOR,
		(vec4) {1.0, 1.0, 1.0, 1.0}
	);

	for (int i = 0; i < s->models_count; i++) {
		renderer_draw_model(r, s->models[i]);
	}
}

void renderer_draw_model(struct renderer *r, struct model *m)
{
	renderer_use_shader(r, SHADER_DEFAULT);
	mat4 transform;
	glm_mat4_identity(transform);

	glm_translate(transform, m->position);
	glm_scale(transform, m->scale);

	shader_uniform_mat4(r->current_shader, UNIFORM_MODEL, transform);
	shader_uniform_texture2D(r->current_shader, m->texture, 1);


	glBindVertexArray(m->mesh->vao);
	glDrawElements(GL_TRIANGLES, m->mesh->index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void renderer_use_shader(struct renderer *r, shader_type_enum type)
{
	if (type == r->current_shader_type)
		return;

	r->current_shader = r->shaders[type];
	r->current_shader_type = type;
	shader_use(r->current_shader);
}

void renderer_init(struct renderer *r)
{
	r->shaders[SHADER_DEFAULT] = shader_create(
		"res/shaders/default.vert",
		"res/shaders/default.frag"
	);

	r->textures[TEXTURE_PLAYER] = texture_create(
		"res/images/standing-steve.png"
	);


	r->meshes[MESH_QUAD] = mesh_create_quad();
	r->draw_wireframe = false;
	r->current_shader = r->shaders[SHADER_DEFAULT];

	// setting world space to match renderer's resolution
	glm_ortho(
		0, (f32) RENDERER_WIDTH, 0.0, (f32) RENDERER_HEIGHT,
		-1.0, 1.0, r->projection
	);
}

void renderer_destroy(struct renderer *r)
{
	for (int i = 0; i < MAX_SHADERS; i++)
		if (r->shaders[i] != NULL)
			shader_destroy(r->shaders[i]);

	for (int i = 0; i < MAX_MESHES; i++)
		if (r->meshes[i] != NULL)
			mesh_destroy(r->meshes[i]);
}
