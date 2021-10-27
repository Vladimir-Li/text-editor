#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "./font.h"

void SDL_CheckCode(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }
}

void *SDL_CheckPtr(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }

    return ptr;
}

int main(void)
{
    SDL_CheckCode(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = SDL_CheckPtr(SDL_CreateWindow("Text Editor", 
    0, 0, 800, 600, 
    SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = SDL_CheckPtr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    SDL_Surface *surface = SDL_CheckPtr(SDL_CreateRGBSurfaceFrom(FONT,
    FONT_WIDTH,
    FONT_HEIGHT,
    8,
    FONT_WIDTH,
    0xFF,
    0xFF,
    0xFF,
    0xFF));

    SDL_Texture *texture = SDL_CheckPtr(SDL_CreateTexture(renderer, 
    SDL_PIXELFORMAT_INDEX8, 
    SDL_TEXTUREACCESS_STATIC,
    FONT_WIDTH,
    FONT_HEIGHT));

    bool quit = false;
    while (!quit) {
        SDL_Event event = {0};
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    quit = true;
                }break;
            }
        }
        SDL_CheckCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0));
        SDL_CheckCode(SDL_RenderClear(renderer));

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}