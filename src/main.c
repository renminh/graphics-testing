#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "state.h"
#include "graphics/renderer.h"
#include "scene/scene.h"
#include "window/window.h"
#include "input/input.h"

#include "util/time.h"

bool running = true;

int main(int argc, char **argv)
{
	struct renderer renderer;
	struct window window;
	struct scene scene;

	window_gl_create(&window);
	renderer_init(&renderer);
	scene_init(&scene);

	scene_load_level(&scene, &renderer);

	f64 timestep = (1.0 / 120.0);
	f64 last_tick = NOW_SECONDS() - timestep;

	while (running) {
		while (NOW_SECONDS() >= last_tick + timestep) {
			poll_input(&scene);
			window_update_fps(&window);
			last_tick += timestep;

		}
		render(&renderer, &scene);
		SDL_GL_SwapWindow(window.handle);
	}

	scene_destroy(&scene);
	renderer_destroy(&renderer);
	window_gl_destroy(&window);

	return EXIT_SUCCESS;
}

