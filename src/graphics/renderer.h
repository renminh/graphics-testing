#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdbool.h>

#include "../scene/scene.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "../scene/entity.h"
// this is based off a 16x16 tilesmap
#define RENDERER_WIDTH 512
#define RENDERER_HEIGHT 320
#define RENDERER_SCALE 1

struct renderer {
	mat4 projection;

	struct mesh meshes[MAX_MESHES];
	struct texture textures[MAX_TEXTURES];
	struct shader shaders[MAX_SHADERS];

	struct shader current_shader;
	shader_type_enum current_shader_type;
};

void render(struct renderer *r, struct scene *s);
void renderer_draw_entity(struct renderer *r, struct entity *e, struct model *m);
void renderer_use_shader(struct renderer *r, shader_type_enum type);
void renderer_init(struct renderer *r);
void renderer_destroy(struct renderer *r);
void renderer_draw_quad_texture(
	struct renderer *r, texture_type_enum type,
	vec3 position, vec2 scale, vec4 color, 
	vec2 uv_min, vec2 uv_max);

struct mesh *renderer_get_mesh(struct renderer *r, mesh_type_enum type);
struct texture *renderer_get_texture(struct renderer *r, texture_type_enum type);

#endif
