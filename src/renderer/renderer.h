#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <SDL3/SDL_opengl.h>
#include <stdbool.h>

struct renderer {
	bool draw_wireframe;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	struct shader *default_shader;
};

#define DRAW_WIREFRAME(flag) (\
	glPolygonMode(GL_FRONT_AND_BACK, (flag) ? GL_LINE : GL_FILL);) 

void render_init(struct renderer *r);
void render(struct renderer *r);
void render_destroy(struct renderer *r);

void quad_init(struct renderer *r);
void quad_draw(struct renderer *r);

#endif
