#include <stdint.h>
#include <glad/glad.h>

#ifndef SHADER_H
#define SHADER_H

typedef enum {
	U_COLOR,
	U_TEXTURE_ID,
	U_PROJECTION,
	U_MODEL,

	SHADER_UNIFORM_COUNT
} shader_uniform;

struct shader {
	GLuint program;
	GLint *uniforms;
};

struct shader *shader_create(const char *vs_path, const char *fs_path);
void shader_use(struct shader *s);
void shader_destroy(struct shader *s);

#endif
