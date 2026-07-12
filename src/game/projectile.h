#ifndef PROJECTILE_H
#define PROJECTILE_H

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

Projectile create_projectile(Direction initial_direction, float x, float y);

#endif
