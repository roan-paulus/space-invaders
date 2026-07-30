#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>

#include <SDL3/SDL_rect.h>
#include "ship.h"
#include <engine/vec2.h>
#include <engine/physics/direction.h>

struct Projectile {
    SDL_FRect body;
    Vec2 velocity;
    bool out_of_bounds{ false };
};

using Projectiles = std::vector<Projectile>;

Projectile create_projectile(float x, float y);

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer);

void update_projectiles(Projectiles& projectiles, float delta_time);

#endif
