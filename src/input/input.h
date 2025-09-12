#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL_events.h>
#include "../renderer/renderer.h"

void poll_input(bool *running, struct renderer *r);

#endif
