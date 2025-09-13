#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include "glad/glad.h"
#include "shader_utils.h"

/*
 * Uniform Names match the enum in shader.h
 * that is, it must match the index of the enums
 *
 * these names are also taken from the glsl shaders
 */

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

void shader_use(const struct shader *s)
{
	glUseProgram(s->program);
}
 
void shader_destroy(struct shader *s)
{
	glDeleteProgram(s->program);
	free(s->uniforms);
	free(s);
}


void shader_uniform_mat4(struct shader *s, uniform_enum type, mat4 m)
{
	glUniformMatrix4fv(s->uniforms[type], 1, GL_FALSE, (const GLfloat *) m);
}

void shader_uniform_texture2D(struct shader *s, struct texture *t, GLuint n)
{
	glActiveTexture(GL_TEXTURE0 + n);
	glBindTexture(GL_TEXTURE_2D, t->id);
	glUniform1i(s->uniforms[UNIFORM_TEXTURE_ID], n);
}

void shader_uniform_float(struct shader *s, uniform_enum type, f32 f)
{
	glUniform1f(s->uniforms[type], f);
}

void shader_uniform_vec2(struct shader *s, uniform_enum type, vec2 v)
{
	glUniform2f(s->uniforms[type], v[VEC_X], v[VEC_Y]);
}

void shader_uniform_vec3(struct shader *s, uniform_enum type, vec3 v)
{
	glUniform3f(s->uniforms[type], v[VEC_X], v[VEC_Y], v[VEC_Z]);
}

void shader_uniform_vec4(struct shader *s, uniform_enum type, vec4 v)
{
	glUniform4f(s->uniforms[type], v[VEC_X], v[VEC_Y], v[VEC_Z], v[VEC_W]);
}

void shader_uniform_int(struct shader *s, uniform_enum type, i32 v)
{
	glUniform1i(s->uniforms[type], v);
}

void shader_uniform_uint(struct shader *s, uniform_enum type, u32 v)
{
	glUniform1ui(s->uniforms[type], v);
}
