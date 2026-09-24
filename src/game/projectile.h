#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>

#include <SDL3/SDL_rect.h>
#include "SDL3/SDL_render.h"
#include <engine/vec2.h>
#include <engine/physics/direction.h>

enum class ProjectileOwner {
    Player,
    Enemy,
};

struct Projectile {
    SDL_FRect body;
    Vec2 velocity;
    bool out_of_bounds{ false };
    ProjectileOwner owner;
};

using Projectiles = std::vector<Projectile>;

Projectile create_projectile(float x, float y, ProjectileOwner owner, float w = 10, float h = 10);

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer);

bool update_projectiles(Projectiles& projectiles, float delta_time);

#endif
