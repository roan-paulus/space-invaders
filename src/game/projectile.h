#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>

#include <SDL3/SDL_rect.h>
#include "ship.h"
#include "engine/vec2.h"

enum class Direction {
    up,
    down,
    left,
    right,
};

struct Projectile {
    SDL_FRect body;
    Vec2 velocity;
};

using Projectiles = std::vector<Projectile>;

Projectile create_projectile(Direction initial_direction, float x, float y);

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer);

void update_projectiles(Projectiles& projectiles);

#endif
