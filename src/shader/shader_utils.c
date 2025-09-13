#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include "../types.h"
#include "../utils/style.h"
#include <glad/glad.h>

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

void shader_get_uniform_locations(struct shader *s)
{
	s->uniforms = (GLint *) malloc(sizeof(GLint) * MAX_UNIFORMS);

	if (s->uniforms == NULL) {
		perror("malloc");
		exit(1);
	}

	for (int i = 0; i < MAX_UNIFORMS; i++) {
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

GLuint shader_load_source(const char *source, GLenum type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1,  (const GLchar * const *) &source, NULL);
	return id;
}

void shader_compile(GLuint id)
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


void shader_link_program(GLuint shader_program)
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

char *file_to_shader(const char *file_path)
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

