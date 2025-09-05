#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "utils/style.h"

void sdl_gl_init(SDL_Window **window, SDL_GLContext *context) {
    printf(INIT_STR "Initializing OpenGL and SDL Subsystems\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            ERROR_STR "Couldn't initialize SDL subsystems: %s\n", SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    /*
     * Using latest version: 4.6 core
     */
    SDL_GL_LoadLibrary(NULL);
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

void sdl_gl_shutdown(SDL_Window **window, SDL_GLContext *context) {
    printf(END_STR "Terminating the program\n");
    printf(END_STR "Destroying SDL Window\n");
    SDL_DestroyWindow(*window);
    *window = NULL;
    printf(END_STR "Uninitializing SDL Subsystems\n");
    SDL_Quit();
    printf(END_STR "Destroying OpenGL context\n");
    SDL_GL_DestroyContext(*context);
    *context = NULL;

    printf(END_STR "Done!\n");
}
