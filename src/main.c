#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#include <math.h>
// #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "graphics.h"
#include "shaders/shader.h"
// #include "utils/style.h"

int main(int argc, char **argv) {
    int success;
    char infoLog[512];
    SDL_Window *window = NULL;
    SDL_GLContext context = NULL;
    bool running = true;

    sdl_gl_init(&window, &context);

    // build and compile the shader program
    // ------------------------------------
    unsigned int shader_program = glCreateProgram();

    // vertex shader
    shader_t vertex_shader = shader_load_source(
        "shaders/triangle.vert", GL_VERTEX_SHADER
    );
    shader_compile(&vertex_shader);
    shader_attach(shader_program, &vertex_shader);

    // fragment shader
    shader_t fragment_shader = shader_load_source(
        "shaders/color.frag", GL_FRAGMENT_SHADER
    );
    shader_compile(&fragment_shader);
    shader_attach(shader_program, &fragment_shader);

    shader_link_program(shader_program);
    shader_free(&vertex_shader);
    shader_free(&fragment_shader);

    // setup vertex data and buffers then configure vertex attributes
    // ----------------------------------
    float vertices[] = {
        // front face
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f,   // top left
        // second triangle
        0.5f, 0.5f, 0.0f, // top right
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
        (void *) 0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    SDL_Event event;
    uint64_t ticks;
    bool toggle_polygon_mode = false;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_0) {
                    glPolygonMode(GL_FRONT_AND_BACK, (toggle_polygon_mode) ?
                                  GL_LINE : GL_FILL);
                    toggle_polygon_mode = !toggle_polygon_mode;
                } else if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }


        ticks = SDL_GetTicks();
        float time_value = (float) ticks / 1000;
        float green_value = (sin(time_value / 2.0f)) + 0.5f;
        int vertex_color_location = glGetUniformLocation(shader_program, "vertex_color");


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // swap front and back framebuffer
        SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(shader_program);

    sdl_gl_shutdown(&window, &context);
    return 0;
}
