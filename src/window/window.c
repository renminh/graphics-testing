#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

#include "window.h"
#include "../logging/log.h"
#include "SDL3/SDL_error.h"

#define SDLDIE(fmt, ...) ({LOG_ERR(fmt, ##__VA_ARGS__); SDL_Quit(); exit(1);})

void window_gl_create(struct window *w)
{
	LOG_INIT("Initializing SDL window and OpenGL context");

	if (!SDL_Init(SDL_INIT_FLAGS))
		SDLDIE("Failed to initialize SDL subsystems: %s", SDL_GetError());

	if (!SDL_GL_LoadLibrary(NULL))
		SDLDIE("Failed to OpenGL: %s", SDL_GetError());

	LOG_INFO("Setting SDL and OpenGL attributes");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);
	// ensure double buffering is on with 24bit Z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // SDL_DisplayMode current_display;
    // SDL_GetCurrentDisplayMode(current_display.displayID);
	// this provides us with current_display.w and current_display.h 

	SDL_Window *handle = SDL_CreateWindow(
		WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS
	);

	if (handle == NULL)
		SDLDIE("Failed to create SDL window: %s", SDL_GetError());

	w->context = SDL_GL_CreateContext(handle);

	if (w->context == NULL)
		SDLDIE("Couldn't create OpenGL context: %s", SDL_GetError());

	if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
		SDLDIE("Failed to load GLAD");

	// set defaults
	w->handle = handle;
	w->height = WINDOW_HEIGHT;
	w->width = WINDOW_WIDTH;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!SDL_GL_SetSwapInterval(VSYNC_SETTING))
		LOG_WARN("Unable to disable SDL vsync: %s", SDL_GetError());

	
	LOG_INFO("Vendor:   %s", glGetString(GL_VENDOR));
	LOG_INFO("Renderer: %s", glGetString(GL_RENDERER));
	LOG_INFO("Version:  %s", glGetString(GL_VERSION));
	LOG_OK("SDL and OpenGL is initialized");
}

void window_gl_destroy(struct window *w)
{
	LOG_END("Destroying OpenGL context");
	SDL_GL_DestroyContext(w->context);
	w->context = NULL;

	LOG_END("Destroying SDL Window");
	SDL_DestroyWindow(w->handle);
	w->handle = NULL;

	LOG_END("Uninitializing SDL Subsystems");
	SDL_Quit();
}
