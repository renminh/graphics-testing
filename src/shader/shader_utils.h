#ifndef SHADER_UTILS
#define SHADER_UTILS

#include "shader.h"
#include <glad/glad.h>

char *file_to_shader(const char *file_path);
GLuint shader_load_source(const char *source, GLenum type);
void shader_compile(GLuint id);
void shader_link_program(GLuint shader_program);
void shader_get_uniform_locations(struct shader *s);

#endif
