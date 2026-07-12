#include <cstdlib>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "event.h"
#include "init.h"
#include <engine/text/text_renderer.h>

void initialize_sdl(
    SDLContext* ctx, const char* window_title, int window_width,
    int window_height
) {
    constexpr SDL_InitFlags flags = SDL_INIT_EVENTS & SDL_WINDOW_FULLSCREEN;

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

    // SDL_ttf plugin
    // ============================
    bool initialized = TTF_Init();
    if (!initialized) {
        const char* msg = "TTF could not be initialized";
        SDL_Log(msg);
    }
    ctx->text_renderer = {
        .text_engine = TTF_CreateRendererTextEngine(ctx->renderer),
        .font = TTF_OpenFont("/usr/share/fonts/noto/NotoSans-CondensedBold.ttf", 14.0f),
    };
    if (ctx->text_renderer.font == nullptr) {
        SDL_Log("Could not load font: %s", SDL_GetError());
    }
}
