#ifndef SHADER_H
#define SHADER_H

char *parse_shader(char *file_path);

typedef struct shader_t {
    unsigned int id;
    const char *source;
} shader_t;

#endif
