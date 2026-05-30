#include <cstdlib>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>

#include "event.h"
#include "init.h"

void initialize_sdl(
    SDLContext* ctx, const char* window_title, int window_width,
    int window_height
) {
    constexpr SDL_InitFlags flags = SDL_INIT_EVENTS;

    if (!SDL_Init(flags)) {
        SDL_LogError(0, SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    if (!SDL_CreateWindowAndRenderer(
            window_title,
            window_width,
            window_height,
            SDL_WINDOW_RESIZABLE,
            &ctx->window,
            &ctx->renderer
        )) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    SDL_SetRenderLogicalPresentation(
        ctx->renderer,
        window_width,
        window_height,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );
}
