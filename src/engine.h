#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <SDL3/SDL_video.h>
#include "graphics/renderer.h"
#include "window.h"

struct engine {
	bool running;

	struct renderer renderer;
	struct window window;
	SDL_GLContext context;
};

#endif
