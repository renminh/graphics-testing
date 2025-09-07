#include <glad/glad.h>
#include "input.h"
#include <stdio.h>
#include "../utils/style.h"

void poll_input(struct engine *engine)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			engine->running = false;
		}

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_0) {
				glPolygonMode(
					GL_FRONT_AND_BACK, 
					(engine->renderer.draw_wireframe) ? GL_LINE : GL_FILL
				);
				printf(LDBG "%s\n", (engine->renderer.draw_wireframe) ?
					"Wireframe is being drawn" : "Wireframe is off"
				);
				engine->renderer.draw_wireframe = !engine->renderer.draw_wireframe;
			} else if (event.key.key == SDLK_ESCAPE) {
				engine->running = false;
			}
		}
	}

}
