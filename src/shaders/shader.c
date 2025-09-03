#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parse_shader(char *file_path) {
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
            shader_n *= shader_n;
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
