#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "renderer/renderer.h"
#include "window/window.h"
#include "input/input.h"
// #include "shader/shader.h"
#include "texture/texture.h"

int main(int argc, char **argv)
{
	struct renderer renderer;
	struct window window;
	struct texture textures_buffer[1024];


	window_gl_create(&window);
	render_init(&renderer);

	bool running = true;
	while (running) {
		poll_input(&running, &renderer);

		render(&renderer);
		window_update_fps(&window);
		SDL_GL_SwapWindow(window.handle);
	}

	window_gl_destroy(&window);
	return EXIT_SUCCESS;
}

