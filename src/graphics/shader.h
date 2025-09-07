#include <stdint.h>
#include <glad/glad.h>
#include <sys/types.h>

#ifndef SHADER_H
#define SHADER_H

struct shader {
	uint32_t id;
	char *source;
	GLenum type;
};

struct shader shader_load_source(const char *path, GLenum type);
void shader_compile(struct shader *shader);
void shader_attach(uint32_t shader_program, struct shader *shader);
void shader_link_program(uint32_t shader_program);
void shader_free(struct shader *shader);

#endif
