#include <stdint.h>
#include <glad/glad.h>
#include <sys/types.h>

#ifndef SHADER_H
#define SHADER_H

typedef struct shader_t {
    uint32_t id;
    char *source;
    GLenum type;
} shader_t;

shader_t shader_load_source(const char *path, GLenum type);
void shader_compile(shader_t *shader);
void shader_attach(uint32_t shader_program, shader_t *shader);
void shader_link_program(uint32_t shader_program);
void shader_free(shader_t *shader);

#endif
