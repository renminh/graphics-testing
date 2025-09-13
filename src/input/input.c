#include <glad/glad.h>
#include "input.h"
#include <stdio.h>
#include "../utils/style.h"

void poll_input(bool *running, struct renderer *r)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			*running = false;
		}

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_0) {
				r->draw_wireframe = !r->draw_wireframe;
				DRAW_WIREFRAME(r->draw_wireframe);
				printf(LDBG "%s\n", (r->draw_wireframe) ?
					"Wireframe drawn" : "Wireframe is off"
				);
			} else if (event.key.key == SDLK_ESCAPE) {
				*running = false;
			}
		}
	}

}
