#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shader.h"
#include "glad/glad.h"
#include "../utils/style.h"

static char *shader_parse(const char *file_path);

// loads GLSL shader from source
shader_t shader_load_source(const char *path, GLenum type) {
    shader_t shader;
    shader.source = shader_parse(path);
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

void shader_compile(shader_t *shader) {
    int success;
    char info_log[512];

    glCompileShader(shader->id);
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader->id, 512, NULL, info_log);
    }
}

void shader_attach(uint32_t shader_program, shader_t *shader) {
    glAttachShader(shader_program, shader->id);
}

void shader_link_program(uint32_t shader_program) {
    int success;
    char info_log[512];

    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    }
}

void shader_free(shader_t *shader) {
    // fixed memory leak, woops
    glDeleteShader(shader->id);
    free(shader->source);
    shader->source = NULL;
}

static char *shader_parse(const char *file_path) {
    char *shader_source = NULL;
    char *line = NULL;
    size_t line_n = 0;
    size_t shader_n = 256;

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    shader_source = (char *) calloc(1, shader_n);
    if (shader_source == NULL) {
        perror("malloc");
        exit(1);
    }

    size_t characters = 0;
    size_t current_characters = 0;
    while ((characters = getline(&line, &line_n, file)) != -1) {
        current_characters += characters;
        if (current_characters > shader_n - 1) {
            shader_n *= 2;
            shader_source = (char *) realloc(shader_source, shader_n);
            if (shader_source == NULL) {
                perror("realloc");
                exit(1);
            }
        }

        strcat(shader_source, line);
    }

    free(line);
    fclose(file);

    return shader_source;
}
