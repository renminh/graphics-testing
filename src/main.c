#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <stdint.h>

#include "engine.h"
#include "window.h"
#include "input/input.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "utils/time.h"

void render(void);

GLuint vao;
GLuint vbo;
GLuint shader_program;

int main(int argc, char **argv)
{

	struct renderer renderer = {
		.draw_wireframe = false,
	};

	struct window window = {
		.handle = NULL,
		.frames = 0,
	};
	window.last_frame = NOW();
	window.last_second = NOW();

	SDL_GLContext context = NULL;

	struct engine engine = {
		.running = true,
		.renderer = renderer,
		.window = window,
		.context = context
	};

	window_gl_create(&engine.window, &engine.context);

	// shaders
	shader_program = glCreateProgram();
	struct shader vertex_shader = shader_load_source(
		"res/shaders/basic.vert", GL_VERTEX_SHADER
	);
	shader_compile(&vertex_shader);
	shader_attach(shader_program, &vertex_shader);

	struct shader fragment_shader = shader_load_source(
		"res/shaders/basic.frag", GL_FRAGMENT_SHADER
	);
	shader_compile(&fragment_shader);
	shader_attach(shader_program, &fragment_shader);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	// create vertex buffer object to store polygon
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);

	// specify location of data within buffer
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void *)0
	);
	glEnableVertexAttribArray(0);

	shader_link_program(shader_program);
	shader_free(&vertex_shader);
	shader_free(&fragment_shader);
	glUseProgram(shader_program);

	while (engine.running) {
		poll_input(&engine);

		render();
		window_update_fps(&engine.window);
		SDL_GL_SwapWindow(engine.window.handle);
	}

	glDeleteProgram(shader_program);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	window_gl_destroy(&engine.window, &engine.context);
	return EXIT_SUCCESS;
}

void render(void)
{
	// clear render output and depth buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
