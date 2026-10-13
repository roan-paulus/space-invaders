#ifndef SHIP_H
#define SHIP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include <engine/vec2.h>
#include <game/animation.h>
#include <game/texture.h>
#include <game/projectile.h>

#include <window_constants.h>

struct Player {
    static constexpr float width       = 60;
    static constexpr float height      = 30;
    static constexpr float start_pos_x = WINDOW_WIDTH / 2.0f - width / 2;
    static constexpr float start_pos_y = WINDOW_HEIGHT / 8.0f * 7;

    SDL_FRect body;
    Vec2 velocity;
    int lives;
    Texture* texture;
    bool shooting;

    void draw(SDL_Renderer* renderer) {
        SDL_RenderTexture(renderer, texture->texture, &texture->frame, &body);
    }

    void shoot(std::vector<Projectile>& projectiles) {
        Projectile projectile = create_projectile(this->body.x, this->body.y, ProjectileOwner::Player, 5, 30);
        // Center the projectile relative to the player size.
        projectile.body.x = (projectile.body.x + this->body.w / 2) - projectile.body.w / 2;
        // Spawn above the player.
        projectile.body.y -= projectile.body.h;
        projectiles.push_back(projectile);
        shooting = true;
    }
};

#endif
