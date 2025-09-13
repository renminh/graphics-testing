#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdbool.h>

#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../mesh/mesh.h"

struct renderer {
	bool draw_wireframe;
	struct mesh *meshes[MAX_MESHES];
	struct texture *textures[MAX_TEXTURES];
	struct shader *shaders[MAX_SHADERS];
	struct shader *current_shader;
};

#define DRAW_WIREFRAME(flag) ({\
	glPolygonMode(GL_FRONT_AND_BACK, (flag) ? GL_LINE : GL_FILL);}) 

void render_init(struct renderer *r);
void render(struct renderer *r);
void render_destroy(struct renderer *r);

#endif
