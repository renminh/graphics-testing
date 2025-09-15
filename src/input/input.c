#include <glad/glad.h>
#include <SDL3/SDL_events.h>

#include "input.h"
#include "../state.h"
#include "../scene/player.h"

void poll_input(struct scene *s)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}
	}

	const bool *keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_A])
		player_move_left(&s->player, PLAYER_BASE_VELOCITY);

	if (keystates[SDL_SCANCODE_W])
		player_move_up(&s->player, PLAYER_BASE_VELOCITY);

	if (keystates[SDL_SCANCODE_D])
		player_move_right(&s->player, PLAYER_BASE_VELOCITY);

	if (keystates[SDL_SCANCODE_S])
		player_move_down(&s->player, PLAYER_BASE_VELOCITY);


}
