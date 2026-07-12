#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <engine/text/text_renderer.h>

struct SDLContext {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TextRenderer text_renderer;
};

void initialize_sdl(
    SDLContext* ctx, const char* window_title, int window_width,
    int window_height
);

#endif
