#include "projectile.h"

#include <algorithm>

#include <game/enemy_grid.h>

Projectile create_projectile(float x, float y, SDL_Texture* texture) {
    return {
        .body = {
            .x = x,
            .y = y,
            .w = 10,
            .h = 10,
        },
        .velocity = {
            .x = 0,
            .y = -256,
        },
        .out_of_bounds{ false },
        .animation{
            .frame_amount = 1,
            .frame = 0,
            .texture = texture,
            .frame_body{
                .x = 0,
                .y = 0,
                .w = 32,
                .h = 32,
            },
        },
    };
}

void update_projectiles(Projectiles& projectiles, EnemyGrid& enemy_grid, float delta_time) {
    for (auto& proj: projectiles) {
        // Add height to give the effect of leaving the area.
        if (proj.body.y + proj.body.h <= 0) {
            proj.out_of_bounds = true;
        }
        proj.body.x += proj.velocity.x * delta_time;
        proj.body.y += proj.velocity.y * delta_time;
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
}

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer) {
    for (auto proj : projectiles) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &proj.body);
    }
}
