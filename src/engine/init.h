#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

struct SDLContext {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void initialize_sdl(
    SDLContext* ctx, const char* window_title, int window_width,
    int window_height
);

#endif
