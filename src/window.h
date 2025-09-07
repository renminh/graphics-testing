#ifndef WINDOW_H 
#define WINDOW_H 

#include <SDL3/SDL_video.h>
#include <stdint.h>

#define SDL_INIT_FLAGS      (SDL_INIT_VIDEO)
#define SDL_WINDOW_FLAGS    (SDL_WINDOW_OPENGL|\
                             SDL_WINDOW_ALWAYS_ON_TOP)

#define WINDOW_TITLE			"Project Forest"
#define WINDOW_WIDTH			800
#define WINDOW_HEIGHT			600
#define OPENGL_MAJOR_VERSION	4
#define OPENGL_MINOR_VERSION	6
#define OPENGL_PROFILE			SDL_GL_CONTEXT_PROFILE_CORE

/* 
 * this flag attaches itself to SDL_GL_SetSwapInterval
 * the options:
 *		0: off
 *		1: on 
 *		-1: adaptive
 */
#define VSYNC_SETTING 0

struct window {
	SDL_Window *handle;

	// timing variables
	uint64_t last_second;
	uint64_t frames, fps, last_frame, frame_delta;
};

void window_gl_create(struct window *w, SDL_GLContext *context);
void window_gl_destroy(struct window *w, SDL_GLContext *context);

void window_update_fps(struct window *w);

#endif
