#ifndef GAME_ANIMATION
#define GAME_ANIMATION

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <game/timer.h>

struct Animation {
    int frame_amount;
    int frame{ 0 };
    SDL_Texture* texture;
    SDL_FRect frame_body;

    void next() {
        frame = (frame + 1) % frame_amount;
        frame_body.x = frame * frame_body.w;
    }

    void draw(SDL_Renderer* renderer, SDL_FRect* to) {
        SDL_RenderTexture(renderer, texture, &frame_body, to);
    }
};

#endif
