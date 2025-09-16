#include <stdlib.h>
#include <glad/glad.h>

#include "shader.h"
#include "shader_utils.h"
#include "../logging/log.h"

#define CHECK_GL_ERROR(_s) ({ \
	while (glGetError() != GL_NO_ERROR) {}\
	GLenum err=glGetError(); \
	if (err != GL_NO_ERROR) LOG_ERR("%s (GL error: 0x%x)", _s, err);})

struct shader shader_create(const char *vs_path, const char *fs_path)
{
	LOG_INFO("Creating shaders for %s and %s", vs_path, fs_path);

	struct shader shader = {0};

	char *vertex_source = shader_read_file(vs_path);
	char *fragment_source = shader_read_file(fs_path);

	GLuint vertex = shader_load_source(vertex_source, GL_VERTEX_SHADER);
	GLuint fragment = shader_load_source(fragment_source, GL_FRAGMENT_SHADER);
	free(vertex_source);
	free(fragment_source);
	vertex_source = NULL;
	fragment_source = NULL;

	shader_compile(vertex);
	shader_compile(fragment);

	shader.id = glCreateProgram();

	/*
	 * binding program object must be done to access uniforms, although GL 4.1 allows 
	 * the use  of "glProgramUniform()" which takes the program object to modify.
	 *
	 * https://stackoverflow.com/questions/42357380/why-must-i-use-a-shader-program-before-i-can-set-its-uniforms
	 */
	glUseProgram(shader.id);


	if (shader.id == 0) {
		LOG_ERR("Failed to create OpenGL shader program");
		exit(1);
	}

	glAttachShader(shader.id, vertex);
	CHECK_GL_ERROR("Vertex shader failed to attach");

	glAttachShader(shader.id, fragment);
	CHECK_GL_ERROR("Fragment shader failed to attach");

	shader_link_program(shader.id);
	shader_get_uniform_locations(&shader);

	glDeleteShader(vertex);
	CHECK_GL_ERROR("Vertex shader failed to be deleted");

	glDeleteShader(fragment);
	CHECK_GL_ERROR("Fragment shader failed to be deleted");

	return shader;
}

void shader_use(const struct shader *s)
{
	/*
	 * If program is zero, then the current rendering state refers to an 
	 * invalid program object and the results of shader execution are 
	 * undefined. However, this is not an error.
	 */
	if (s == NULL) {
		LOG_ERR("An invalid null shader was just passed");
		exit(1);
	}

	if (s->id == 0) {
		LOG_WARN("An invalid program object was passed, " \
		   "undefined behaviour will occur");
	}

	glUseProgram(s->id);
	CHECK_GL_ERROR("Failed to use shader program");
}
 
void shader_destroy(struct shader *s)
{
	glDeleteProgram(s->id);
	CHECK_GL_ERROR("Failed to delete shader program");

	free(s->uniforms);
	s->uniforms = NULL;
}


void shader_uniform_mat4(struct shader *s, uniform_enum type, mat4 m)
{
	glUniformMatrix4fv(s->uniforms[type], 1, GL_FALSE, (const GLfloat *) m);
}

void shader_uniform_texture2D(struct shader *s, struct texture *t, GLuint n)
{
	if (glIsTexture(t->id) != GL_TRUE) {
		LOG_ERR("'%d' is not a valid texture", t->id);
		return;
	}
	glActiveTexture(GL_TEXTURE0 + n);
	CHECK_GL_ERROR("Failed to activate texture");

	glBindTexture(GL_TEXTURE_2D, t->id);
	CHECK_GL_ERROR("Failed to bind texture");


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
