#include <glad/glad.h>
#include <SDL3/SDL_events.h>
#include <stdio.h>

#include "input.h"
#include "../utils/style.h"
#include "../state.h"

void poll_input(struct renderer *r, struct scene *s)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_0) {
				r->draw_wireframe = !r->draw_wireframe;
				DRAW_WIREFRAME(r->draw_wireframe);
				printf(LDBG "%s\n", (r->draw_wireframe) ?
					"Wireframe drawn" : "Wireframe is off"
				);
			}

			if (event.key.key == SDLK_ESCAPE) {
				running = false;
			}

			if (event.key.key == SDLK_A) {
				s->models[0]->position[0] -= 20;
			}

			if (event.key.key == SDLK_W) {
				s->models[0]->position[1] += 20;
			}

			if (event.key.key == SDLK_D) {
				s->models[0]->position[0] += 20;
			}

			if (event.key.key == SDLK_S) {
				s->models[0]->position[1] -= 20;
			}


		}
	}

}
