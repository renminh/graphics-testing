#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <stb/stb_image.h>
#include <cglm/cam.h>

#include "renderer.h"
#include "../types.h"
#include "mesh.h"
#include "shader.h"
#include "atlas.h"
#include "texture.h"

struct atlas atlas;

void render(struct renderer *r, struct scene *s)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer_use_shader(r, SHADER_DEFAULT);
	shader_uniform_mat4(&r->current_shader, UNIFORM_PROJECTION, r->projection);

	vec2 uv_min, uv_max;
	atlas_get_uv(
		atlas, 
		(ivec2) {1, 0},
		uv_min, 
		uv_max
	);

	renderer_draw_quad_texture(
		r, TEXTURE_TILES,
		(vec3) {200, 100, -0.5},
		(vec3) {32, 32, 1},
		(vec4) {1, 1, 1, 1},
		uv_min, uv_max
	);

	atlas_get_uv(
		atlas, 
		(ivec2) {0, 0},
		uv_min, 
		uv_max
	);

	renderer_draw_quad_texture(
		r, TEXTURE_TILES,
		(vec3) {232, 100, -0.5},
		(vec3) {32, 32, 1},
		(vec4) {1, 1, 1, 1},
		uv_min, uv_max
	);


	renderer_draw_entity(r, &s->player, &s->models[s->player.model_type]);

	for (size_t i = 0; i < array_list_length(s->entities); i++) {
		struct entity *e = array_list_get(s->entities, i);
		struct model *m = &s->models[e->model_type];
		renderer_draw_entity(r, e, m);
	}
}

void renderer_draw_entity(struct renderer *r, struct entity *e, struct model *m)
{
	shader_uniform_texture2D(&r->current_shader, m->texture, 0);
	

	mat4 transform;
	glm_mat4_identity(transform);
	glm_translate(transform, e->transform.position);
	glm_scale(transform, e->transform.scale);

	shader_uniform_mat4(&r->current_shader, UNIFORM_MODEL, transform);
	shader_uniform_vec4(&r->current_shader, UNIFORM_UV, (vec4){0,0,1,1});

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
	shader_use(&r->current_shader);
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

	r->textures[TEXTURE_TILES] = texture_create(
		"res/images/tile-sheet.png"
	);

	atlas = atlas_create(
		*renderer_get_texture(r, TEXTURE_TILES),
		(ivec2) {300, 300}
	);

	r->meshes[MESH_QUAD] = mesh_create_quad();
	r->current_shader = r->shaders[SHADER_DEFAULT];
	r->current_shader_type = SHADER_DEFAULT;

	// setting world space to match renderer's resolution
	glm_ortho(
		0, 
		(f32) RENDERER_WIDTH / RENDERER_SCALE, 
		0.0, 
		(f32) RENDERER_HEIGHT / RENDERER_SCALE,
		-1.0, 1.0, r->projection
	);

}

void renderer_draw_quad_texture(
	struct renderer *r, texture_type_enum type,
	vec3 position, vec3 scale, vec4 color, 
	vec2 uv_min, vec2 uv_max)
{
	struct mesh *mesh = renderer_get_mesh(r, MESH_QUAD);
	vec4 tile_uv;
	glm_vec4_copy(
		(vec4) {uv_min[VEC_X], uv_min[VEC_Y], uv_max[VEC_X], uv_max[VEC_Y]},
		tile_uv
	);
		

	renderer_use_shader(r, SHADER_DEFAULT);

	mat4 transform;
	glm_mat4_identity(transform);
	glm_mat4_identity(transform);
	glm_translate(transform, position);
	glm_scale(transform, scale);

	shader_uniform_mat4(&r->current_shader, UNIFORM_MODEL, transform);
	shader_uniform_texture2D(&r->current_shader, renderer_get_texture(r, type), 0);
	shader_uniform_vec4(&r->current_shader, UNIFORM_COLOR, color);
	shader_uniform_vec4(&r->current_shader, UNIFORM_UV, tile_uv);

	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void renderer_destroy(struct renderer *r)
{
	for (int i = 0; i < MAX_SHADERS; i++)
		shader_destroy(&r->shaders[i]);

	for (int i = 0; i < MAX_MESHES; i++)
		mesh_destroy(&r->meshes[i]);
}

struct mesh *renderer_get_mesh(struct renderer *r, mesh_type_enum type)
{
	return &r->meshes[type];
}

struct texture *renderer_get_texture(struct renderer *r, texture_type_enum type)
{
	return &r->textures[type];
}
