#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>
#include <stdlib.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_init.h>
#include "style.h"

#define SDLDIE(msg) ({\
	fprintf(stderr, LERR "%s: %s\n", (msg), SDL_GetError());\
	SDL_Quit();\
	exit(EXIT_FAILURE);})

#endif
