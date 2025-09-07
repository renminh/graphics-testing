#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shader.h"
#include "../utils/style.h"

static char *file_to_shader(const char *file_path);

// loads GLSL shader from source
struct shader shader_load_source(const char *path, GLenum type)
{
	struct shader shader;
	shader.source = file_to_shader(path);
	shader.type = type;
	shader.id = glCreateShader(type);

	// replaces the source code in a shader
	glShaderSource(
		shader.id,
		1, 
		(const GLchar * const *) &shader.source, 
		NULL
	);

	return shader;
}

void shader_compile(struct shader *shader)
{
	int success;
	char info_log[512];

	glCompileShader(shader->id);
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader->id, 512, NULL, info_log);
		fprintf(
			stderr, LERR "Shader failed to compile: %s\n", info_log
		);
	}
	printf(LOK "Shader compiled!\n");
}

void shader_attach(uint32_t shader_program, struct shader *shader)
{
	glAttachShader(shader_program, shader->id);
}

void shader_link_program(uint32_t shader_program)
{
	int success;
	char info_log[512];

	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
	}
}

void shader_free(struct shader *shader)
{
	// fixed memory leak, woops
	glDeleteShader(shader->id);
	free(shader->source);
	shader->source = NULL;
}

static char *file_to_shader(const char *file_path)
{
	char *buffer = NULL;
	long length;

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
