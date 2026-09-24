#include "projectile.h"

#include <algorithm>
#include <iostream>

#include <SDL3/SDL_render.h>

#include <game/enemy_grid.h>
#include <game/ship.h>

Projectile create_projectile(float x, float y, ProjectileOwner owner, float w, float h) {
    return {
        .body = {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
        .velocity = {
            .x = 0,
            .y = -500,
        },
        .out_of_bounds = false,
        .owner = owner,
    };
}

bool update_projectiles(Projectiles& projectiles, float delta_time) {
    bool did_ship_shooting_stop = false;

    for (auto& proj: projectiles) {
        // Add height to give the effect of leaving the area.
        if (proj.body.y + proj.body.h <= 0) {
            proj.out_of_bounds = true;
        }
        proj.body.x += proj.velocity.x * delta_time;
        proj.body.y += proj.velocity.y * delta_time;

        if (proj.out_of_bounds && proj.owner == ProjectileOwner::Player) {
            did_ship_shooting_stop = true;
        }
    }

    projectiles.erase(
        std::remove_if(
            projectiles.begin(), projectiles.end(),
            [](const Projectile& entity) {
                return entity.out_of_bounds;
            }
        ),
        projectiles.end()
    );

    return did_ship_shooting_stop;
}

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer) {
    for (auto& proj : projectiles) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &proj.body);
        SDL_RenderRect(renderer, &proj.body);
    }
}
