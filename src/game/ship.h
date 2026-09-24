#ifndef SHIP_H
#define SHIP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include <engine/vec2.h>
#include <game/animation.h>
#include <game/texture.h>
#include <game/projectile.h>

struct Ship {
    SDL_FRect body;
    Vec2 velocity;
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
