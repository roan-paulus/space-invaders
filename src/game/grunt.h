#pragma once

#include <array>

#include <game/config.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

struct Grunt {
    int hitpoints;
    SDL_FRect body;

    void draw(SDL_Renderer* renderer);
};

using Grunts = std::array<Grunt, enemy_col_amount>;
