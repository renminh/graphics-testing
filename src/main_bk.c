#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define INIT_STR "["ANSI_COLOR_CYAN"INIT"ANSI_COLOR_RESET"]\t\t"
#define ERROR_STR "["ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"]\t\t"
#define SUCCESS_STR "["ANSI_COLOR_GREEN"SUCCESS"ANSI_COLOR_RESET"]\t"
#define END_STR "["ANSI_COLOR_YELLOW"END"ANSI_COLOR_RESET"]\t\t"
#define INFO_STR "[INFO]\t\t"


const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


void initialize(SDL_Window **window, SDL_GLContext *context) {
    printf(INIT_STR "Initializing OpenGL and SDL Subsystems\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            ERROR_STR "Couldn't initialize SDL subsystems: %s\n", SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    SDL_GL_LoadLibrary(NULL);

    // using core 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    // ensure double buffering is on with 24bit Z buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    *window = SDL_CreateWindow(
        WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS
    );

    if (*window == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            ERROR_STR "Couldn't create SDL window: %s\n",
            SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    *context = SDL_GL_CreateContext(*window);

    if (*context == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            ERROR_STR "Couldn't creating OpenGL context: %s\n",
            SDL_GetError()
        );
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(1);
    }

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            ERROR_STR "Failed to load GLAD: %s\n", SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    // post configuration during initialization
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    printf(INFO_STR "Vendor:   %s\n", glGetString(GL_VENDOR));
    printf(INFO_STR "Renderer: %s\n", glGetString(GL_RENDERER));
    printf(INFO_STR "Version:  %s\n", glGetString(GL_VERSION));
    printf(SUCCESS_STR "Successfully initialized\n");
}

void deinitialize(SDL_Window **window, SDL_GLContext *context) {
    printf(END_STR "Terminating the program\n");
    printf(END_STR "Destroying SDL Window\n");
    SDL_DestroyWindow(*window);
    printf(END_STR "Uninitializing SDL Subsystems\n");
    SDL_Quit();
    printf(END_STR "Destroying OpenGL context\n");
    SDL_GL_DestroyContext(*context);

    printf(END_STR "Done!\n");
}

int main(int argc, char **argv) {
    int success;
    char infoLog[512];
    SDL_Window *window = NULL;
    SDL_GLContext context = NULL;
    bool running = true;

    initialize(&window, &context);

    // build and compile the shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf(ERROR_STR "Vertex: compilation failed: %s\n", infoLog);
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf(ERROR_STR "Fragment: compilation failed: %s\n", infoLog);
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // setup vertex data and buffers then configure vertex attributes
    // ----------------------------------
    float vertices[] = {
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


    bool toggle_polygon_mode = false;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.key.key == SDLK_0 && event.key.down) {
                (toggle_polygon_mode) ? 
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) :
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                toggle_polygon_mode = !toggle_polygon_mode;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // swap front and back framebuffer
        SDL_GL_SwapWindow(window);

    }


    deinitialize(&window, &context);

    return 0;
}
