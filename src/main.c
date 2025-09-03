#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void initialize(SDL_Window **window, SDL_GLContext *context) {
    printf("[INIT] Initializing GL, window, and context...\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            "[ERROR] Couldn't initialize SDL subsystems: %s\n", SDL_GetError()
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

    *window = SDL_CreateWindow(
        WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS
    );

    if (*window == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "[ERROR] Couldn't create SDL window: %s\n",
            SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    *context = SDL_GL_CreateContext(*window);

    if (*context == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "[ERROR] Couldn't creating OpenGL context: %s\n",
            SDL_GetError()
        );
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(1);
    }

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            "[ERROR] Failed to load GLAD: %s\n", SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    printf("Information on GL Provider\n");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("[SUCCESS] Finished initializing...\n");
}

void deinitialize(SDL_Window **window, SDL_GLContext *context) {
    printf("Ending the program\n");
    printf("Destroying Window\n");
    SDL_DestroyWindow(*window);
    printf("Unitilization subsystems\n");
    SDL_Quit();
    SDL_GL_DestroyContext(*context);

    printf("all good!\n");
}

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_GLContext context = NULL;
    SDL_Event event;
    bool running = true;

    initialize(&window, &context);

    // tell GL the size of the rendering window
    // processed coordinates in OpenGL are between -1 and 1
    // this maps out to the defined width and height for the window
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // game loop this will contain the input, rendering, and what not
    // or could be considered render loop if nothing else
    // an iteration of a render loop is called a frame
    while (running) {
        // poll for and process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // ClearColor is state setting and Clear is state using
        // Clear grabs the current state and uses it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap front and back framebuffer
        SDL_GL_SwapWindow(window);

    }

    deinitialize(&window, &context);

    return 0;
}

/*
 * Some platforms would rather your program operate in chunks. 
 * Most of the time, games tend to look like this at the highest level:

int main(int argc, char **argv)
{
    initialize();
    while (keep_running()) {
        handle_new_events();
        do_one_frame_of_stuff();
    }
    deinitialize();
}

*/
