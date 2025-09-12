#include <stdio.h>
#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "window.h"
#include "SDL3/SDL_video.h"
#include "../utils/time.h"
#include "../utils/utils.h"
#include "../utils/style.h"
#include "../types.h"

void window_gl_create(struct window *w)
{
	printf(LINIT "Initializing OpenGL and SDL Subsystems\n");

	if (!SDL_Init(SDL_INIT_VIDEO))
		SDLDIE("Couldn't initialize SDL subsystems");

	if (!SDL_GL_LoadLibrary(NULL))
		SDLDIE("Failed to load OpenGL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);

	// ensure double buffering is on with 24bit Z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/*
    SDL_DisplayMode current_display;
    SDL_GetCurrentDisplayMode(current_display.displayID);
    */ // this provides us with current_display.w and current_display.h 

	SDL_Window *handle = SDL_CreateWindow(
		WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS
	);

	if (handle == NULL)
		SDLDIE("Couldn't create SDL window");

	w->context = SDL_GL_CreateContext(handle);

	if (w->context == NULL)
		SDLDIE("Couldn't create OpenGL context");

	if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
		SDLDIE("Failed to load GLAD");

	// set defaults
	w->handle = handle;
	w->frames = 0;
	w->last_frame = NOW();
	w->last_second = NOW();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	w->height = WINDOW_HEIGHT;
	w->width = WINDOW_WIDTH;

	// set context inital attributes
	if (!SDL_GL_SetSwapInterval(VSYNC_SETTING)) {
		printf(LWARN "Unable to disable vsync: %s\n", SDL_GetError());
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	printf(LINFO "Vendor:   %s\n", glGetString(GL_VENDOR));
	printf(LINFO "Renderer: %s\n", glGetString(GL_RENDERER));
	printf(LINFO "Version:  %s\n", glGetString(GL_VERSION));
	printf(LOK "Successfully initialized\n");
}

void window_gl_destroy(struct window *w)
{
	printf(LEND "Destroying OpenGL context\n");
	SDL_GL_DestroyContext(w->context);
	w->context = NULL;

	printf(LEND "Destroying SDL Window\n");
	SDL_DestroyWindow(w->handle);
	w->handle = NULL;

	printf(LEND "Uninitializing SDL Subsystems\n");
	SDL_Quit();
}

void window_update_fps(struct window *w)
{
	const u64 now = NOW();

	w->frame_delta = now - w->last_frame;
	w->last_frame = now;

	if (now - w->last_second > NS_PER_SECOND) {
		w->fps = w->frames;
		w->frames = 0;
		w->last_second = now;

		printf("FPS: %lu\n", w->fps);
	}

	w->frames += 1;
}
