#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdbool.h>

#include "../scene/scene.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../mesh/mesh.h"
#include "../model/model.h"

// this is based off a 16x16 tiles
#define RENDERER_WIDTH 512
#define RENDERER_HEIGHT 320

struct renderer {
	bool draw_wireframe;
	mat4 projection;
	struct mesh *meshes[MAX_MESHES];
	struct texture *textures[MAX_TEXTURES];
	struct shader *shaders[MAX_SHADERS];
	struct shader *current_shader;
	shader_type_enum current_shader_type;
};

#define DRAW_WIREFRAME(flag) ({\
	glPolygonMode(GL_FRONT_AND_BACK, (flag) ? GL_LINE : GL_FILL);}) 

void render(struct renderer *r, struct scene *s);
void renderer_draw_model(struct renderer *r, struct model *m);
void renderer_use_shader(struct renderer *r, shader_type_enum type);
void renderer_init(struct renderer *r);
void renderer_destroy(struct renderer *r);

#endif
