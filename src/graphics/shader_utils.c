#include <stdlib.h>
#include <glad/glad.h>

#include "../logging/log.h"
#include "shader.h"
#include "../types.h"

#define CHECK_GL_ERROR(_s) ({ \
	while (glGetError() != GL_NO_ERROR) {}\
	GLenum err=glGetError(); \
	if (err != GL_NO_ERROR) LOG_ERR("%s (GL error: 0x%x)", _s, err);})

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
	"uv"
};

static_assert(
	sizeof(uniform_names) / sizeof(uniform_names[0]) == MAX_UNIFORMS,
	"Uniform names do not match the number of uniforms declared in the enum"
);

void shader_get_uniform_locations(struct shader *s)
{

	/*
	 * binding program object must be done to access uniforms, although GL 4.1 allows 
	 * the use  of "glProgramUniform()" which takes the program object to modify.
	 *
	 * https://stackoverflow.com/questions/42357380/why-must-i-use-a-shader-program-before-i-can-set-its-uniforms
	 */
	shader_use(s);

	s->uniforms = (GLint *) malloc(sizeof(GLint) * MAX_UNIFORMS);
	LOG_INFO("Retrieving uniforms from shader");

	if (s->uniforms == NULL) {
		LOG_ERR("malloc failed to allocate memory for the shader uniforms");
		exit(1);
	}

	for (u32 i = 0; i < MAX_UNIFORMS; i++) {
		GLint id = glGetUniformLocation(s->id, uniform_names[i]);

		if (id == -1) {
			LOG_ERR("Failed to retrieve uniform \"%s\"", uniform_names[i]);
		} else {
			LOG_INFO("Retrieved uniform \"%s\"", uniform_names[i]);
			s->uniforms[i] = id;
		}
	}
}

GLuint shader_load_source(const char *source, GLenum type)
{
	GLuint id = glCreateShader(type);
	if (id == 0) {
		LOG_ERR("Failed to create OpenGL shader for %s", source);
		exit(1);
	}

	glShaderSource(id, 1,  (const GLchar * const *) &source, NULL);
	CHECK_GL_ERROR("Failed to create an OpenGL shader object");
	return id;
}

void shader_compile(GLuint shader_id)
{
	i32 success;
	char info_log[512];

	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, info_log);
		LOG_ERR("Shader failed to compile: %s", info_log);
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
		LOG_ERR("Failed to link shader program: %s", info_log);
	}
}


char *shader_read_file(const char *file_path)
{
	char *buffer = NULL;
	i64 length = 0;

	FILE *file = fopen(file_path, "rb");
	if (file == NULL) {
		LOG_ERR("Failed to open file: \"%s\"", file_path);
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

