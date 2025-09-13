#include "mesh/mesh.h"
#include "texture/texture.h"
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "state.h"
#include "renderer/renderer.h"
#include "scene/scene.h"
#include "window/window.h"
#include "input/input.h"

bool running = true;

int main(int argc, char **argv)
{
	struct renderer renderer;
	struct window window;
	struct scene scene;

	window_gl_create(&window);
	renderer_init(&renderer);
	scene_init(&scene);

	scene_create_model(
		&scene,
		renderer.meshes[MESH_QUAD],
		renderer.textures[TEXTURE_PLAYER],
		(vec3) {450, 200, 0},
		(vec3) {32, 32, 1},
		0
	);

	while (running) {
		poll_input(&renderer, &scene);

		render(&renderer, &scene);
		window_update_fps(&window);
		SDL_GL_SwapWindow(window.handle);
	}

	scene_destroy(&scene);
	renderer_destroy(&renderer);
	window_gl_destroy(&window);

	return EXIT_SUCCESS;
}

