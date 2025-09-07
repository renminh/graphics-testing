#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

struct renderer {
	bool draw_wireframe;
};

#define DRAW_WIREFRAME(bool) (\glPolygonMode(GL_FRONT_AND_BACK, (bool) ? GL_LINE : GL_FILL);) 

#endif
