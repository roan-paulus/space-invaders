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
        , enabled{ true }
    {}
    Grunt(int hitpoints, SDL_FRect body, Texture* texture)
        : hitpoints{hitpoints}
        , body{body}
        , texture{texture}
    {}

    void draw(SDL_Renderer* renderer, SDL_FRect& frame_body) {
        SDL_RenderTexture(renderer, texture->texture, &frame_body, &body);
    }

    bool has_collision(Projectile& projectile) {
        const auto g = body;
        const auto p = projectile.body;

        float g_x2 = g.x + g.w;
        float g_y2 = g.y + g.h;

        float p_x2 = p.x + p.w;
        float p_y2 = p.y + p.h;

        return g.x < p_x2 && g_x2 > p.x
            && g.y < p_y2 && g_y2 > p.y;
    }
};

using Grunts = std::array<Grunt, enemy_col_amount>;
