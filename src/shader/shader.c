#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shader.h"
#include "../types.h"
#include "../utils/style.h"
#include <glad/glad.h>

static char *file_to_shader(const char *file_path);
static GLuint shader_load_source(const char *source, GLenum type);
static void shader_compile(GLuint id);
static void shader_link_program(GLuint shader_program);
static void shader_get_uniform_locations(struct shader *s);

/*
 * Uniform Names match the enum in shader.h
 * that is, it must match the index of the enums
 *
 * these names are also taken from the glsl shaders
 */
static const char *uniform_names[] = {
	"color",
	"texture_id",
	"projection",
	"model",
};

struct shader *shader_create(const char *vs_path, const char *fs_path)
{
	struct shader *shader = NULL;

	char *vertex_source = file_to_shader(vs_path);
	char *fragment_source = file_to_shader(fs_path);

	GLuint vertex = shader_load_source(vertex_source, GL_VERTEX_SHADER);
	GLuint fragment = shader_load_source(fragment_source, GL_FRAGMENT_SHADER);

	shader_compile(vertex);
	shader_compile(fragment);

	// after shader compilation
	shader = (struct shader *) malloc(sizeof(struct shader));

	if (shader == NULL) {
		perror("malloc");
		exit(1);
	}

	shader->program = glCreateProgram();

	glAttachShader(shader->program, vertex);
	glAttachShader(shader->program, fragment);
	shader_link_program(shader->program);
	shader_get_uniform_locations(shader);

	// cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	free(vertex_source);
	free(fragment_source);

	return shader;
}

void shader_use(struct shader *s)
{
	glUseProgram(s->program);
}
 
void shader_destroy(struct shader *s)
{
	glDeleteProgram(s->program);
	free(s->uniforms);
	free(s);
}

GLuint shader_get_program(struct shader *s)
{
	return s->program;
}

static void shader_get_uniform_locations(struct shader *s)
{
	s->uniforms = (GLint *) malloc(sizeof(GLint) * SHADER_UNIFORM_COUNT);

	if (s->uniforms == NULL) {
		perror("malloc");
		exit(1);
	}

	for (int i = 0; i < SHADER_UNIFORM_COUNT; i++) {
		GLint id = glGetUniformLocation(s->program, uniform_names[i]);

		if (id == -1) {
			fprintf(
				stderr,
				LERR "Failed to retrive uniform '%s'\n", uniform_names[i]
			);
		}

		s->uniforms[i] = id;
	}
}

// loads GLSL shader from source
static GLuint shader_load_source(const char *source, GLenum type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1,  (const GLchar * const *) &source, NULL);
	return id;
}

static void shader_compile(GLuint id)
{
	i32 success;
	char info_log[512];

	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, info_log);
		fprintf(
			stderr, LERR "Shader failed to compile: %s\n", info_log
		);
	} else {
		printf(LOK "Shader compiled!\n");
	}
}


static void shader_link_program(GLuint shader_program)
{
	i32 success;
	char info_log[512];

	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		fprintf(
			stderr, LERR "Shader program failed to link: %s\n", info_log
		);

	}
}

static char *file_to_shader(const char *file_path)
{
	char *buffer = NULL;
	i64 length;

	FILE *file = fopen(file_path, "rb");
	if (file == NULL) {
		perror("fopen");
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	// include null terminator
	buffer = (char *)malloc(length + 1);
	fseek(file, 0, SEEK_SET);
	fread(buffer, length, 1, file);
	fclose(file);
	buffer[length] = '\0';

	return buffer;
}
