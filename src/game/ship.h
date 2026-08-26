#ifndef SHIP_H
#define SHIP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include "window_constants.h"
#include <engine/vec2.h>
#include <game/animation.h>
#include <game/texture.h>

struct Ship {
    SDL_FRect body;
    Vec2 velocity;
    Texture* texture;

    void draw(SDL_Renderer* renderer) {
        SDL_RenderTexture(renderer, texture->texture, &texture->frame, &body);
    }
};

#endif
