#pragma once

#include <array>

#include <game/config.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <game/projectile.h>
#include <game/texture.h>

struct Grunt {
    int hitpoints;
    SDL_FRect body;
    Texture* texture;
    bool enabled;

    Grunt()
        : hitpoints{ 0 }
        , body{}
        , texture{ nullptr }
        , enabled{ false }
    {}
    Grunt(int hitpoints, SDL_FRect body, Texture* texture)
        : hitpoints{hitpoints}
        , body{body}
        , texture{texture}
    {}

    void draw(SDL_Renderer* renderer, SDL_FRect& frame_body) {
        SDL_RenderTexture(renderer, texture->texture, &frame_body, &body);
    }
};

using Grunts = std::array<Grunt, enemy_col_amount>;
