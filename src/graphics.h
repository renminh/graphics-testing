#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#ifndef GRAPHICS_H 
#define GRAPHICS_H

#define SDL_INIT_FLAGS      (SDL_INIT_VIDEO)
#define SDL_WINDOW_FLAGS    (SDL_WINDOW_OPENGL| \
                             SDL_WINDOW_ALWAYS_ON_TOP)
#define WINDOW_TITLE "Project Forest"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void sdl_gl_init(SDL_Window **window, SDL_GLContext *context);
void sdl_gl_shutdown(SDL_Window **window, SDL_GLContext *context);

#endif
