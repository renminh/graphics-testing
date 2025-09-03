#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void initialize(SDL_Window *window) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR, 
            "Error initilization SDL subsystems: %s\n", SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow(
        WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS
    );

    if (window == NULL) {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Error creating SDL window: %s\n",
            SDL_GetError()
        );
        SDL_Quit();
        exit(1);
    }
}

void deinitialize(SDL_Window *window) {
    printf("Ending the program\n");
    printf("Destroying Window\n");
    SDL_DestroyWindow(window);
    printf("Unitilization subsystems\n");
    SDL_Quit();

    printf("all good!\n");
}

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    bool running = true;


    initialize(window);

    // game loop this will contain the input, rendering, and what not
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    deinitialize(window);

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
