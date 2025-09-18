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

static vec3 tile_scale = (vec3) {TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, 1};
static vec4 tile_color = (vec4) {1, 1, 1, 1};

static void render_draw_tile(struct renderer *r, vec3 pos, tile_type_enum type);
static void renderer_draw_quad_texture(
	struct renderer *r, texture_type_enum type,
	vec3 position, vec3 scale, vec4 color, 
	vec2 uv_min, vec2 uv_max);
void render_draw_tilemap(struct renderer *r);

void render(struct renderer *r, struct scene *s)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer_use_shader(r, SHADER_DEFAULT);

	scene_update_camera(s, s->player.transform.position);
	shader_uniform_mat4(&r->current_shader, UNIFORM_PROJECTION, s->camera.projection);
	shader_uniform_mat4(&r->current_shader, UNIFORM_VIEW, s->camera.view);


	renderer_draw_entity(r, &s->player, &s->models[s->player.model_type]);
	render_draw_tilemap(r);

	for (size_t i = 0; i < array_list_length(s->entities); i++) {
		struct entity *e = array_list_get(s->entities, i);
		struct model *m = &s->models[e->model_type];
		renderer_draw_entity(r, e, m);
	}
}

void renderer_draw_entity(struct renderer *r, struct entity *e, struct model *m)
{
	mat4 transform;
	glm_mat4_identity(transform);
	glm_translate(transform, e->transform.position);
	glm_scale(transform, e->transform.scale);

	shader_uniform_mat4(&r->current_shader, UNIFORM_MODEL, transform);
	shader_uniform_vec4(&r->current_shader, UNIFORM_UV, (vec4){0,0,1,1});
	shader_uniform_vec4(&r->current_shader, UNIFORM_COLOR, (vec4) {1, 1, 1, 1});

	shader_uniform_bool(&r->current_shader, UNIFORM_USE_TEXTURE, USE_TEXTURE);
	shader_uniform_texture2D(&r->current_shader, m->texture, 0);

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
	glPolygonMode(GL_FRONT_AND_BACK, DRAW_WIREFRAME ? GL_LINE : GL_FILL);
	//glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	r->shaders[SHADER_DEFAULT] = shader_create(
		"res/shaders/default.vert",
		"res/shaders/default.frag"
	);

	r->textures[TEXTURE_PLAYER] = texture_create("res/textures/standing-steve.png");
	r->textures[TEXTURE_TILES] = texture_create("res/textures/tile-sheet.png");


	r->meshes[MESH_QUAD] = mesh_create_quad();
	r->current_shader = r->shaders[SHADER_DEFAULT];
	r->current_shader_type = SHADER_DEFAULT;


	atlas = atlas_create(
		renderer_get_texture(r, TEXTURE_TILES),
		(ivec2) {SPRITE_SIZE_X, SPRITE_SIZE_Y}
	);
}

void render_draw_tile(struct renderer *r, vec3 pos, tile_type_enum type)
{
	vec2 uv_min, uv_max;
	atlas_get_tile(&atlas, type, uv_min, uv_max);
	renderer_draw_quad_texture(
		r, TEXTURE_TILES, pos, tile_scale, tile_color, uv_min, uv_max
	);
}

void render_draw_tilemap(struct renderer *r)
{
	u32 offset_x = 0;
	u32 offset_y = 0;

	u32 tilemap[][12] = {
		{0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0},
		{0, 1, 1, 0, 1, 1, 2, 3, 2, 2, 2, 2},
		{0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2},
		{3, 3, 2, 3, 3, 3, 3, 3, 2, 2, 2, 2},
		{3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2},
		{3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3},
		{3, 3, 2, 3, 3, 3, 3, 3, 2, 2, 3, 3},
		{1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 3},
		{1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 3}
	};

	// SLOW USE BATCHING TO RENDER ALL OF THIS INSTEAD OF SENDING n * n
	// DRAW CALLS
	for (u32 row = 0; row < sizeof(tilemap)/sizeof(tilemap[0]); row++) {
		for (u32 col = 0; col < sizeof(tilemap[0])/sizeof(tilemap[0][0]); col++) {
			int flipped_row = sizeof(tilemap)/sizeof(tilemap[0]) - 1 - row;
			int y = offset_y + flipped_row * TILE_PIXEL_SIZE_Y;
			render_draw_tile(
				r, 
				(vec3) {col * TILE_PIXEL_SIZE_X + offset_x, y, 0},
				tilemap[row][col]
			);
		}
	}
}

void renderer_destroy(struct renderer *r)
{
	for (int i = 0; i < MAX_SHADERS; i++)
		shader_destroy(&r->shaders[i]);

	for (int i = 0; i < MAX_TEXTURES; i++)
		texture_destroy(&r->textures[i]);

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

static void renderer_draw_quad_texture(
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
	glm_translate(transform, position);
	glm_scale(transform, scale);

	shader_uniform_mat4(&r->current_shader, UNIFORM_MODEL, transform);
	shader_uniform_texture2D(&r->current_shader, renderer_get_texture(r, type), 0);
	shader_uniform_bool(&r->current_shader, UNIFORM_USE_TEXTURE, USE_TEXTURE);
	shader_uniform_vec4(&r->current_shader, UNIFORM_COLOR, color);
	shader_uniform_vec4(&r->current_shader, UNIFORM_UV, tile_uv);

	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
