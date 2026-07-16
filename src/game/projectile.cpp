#include "projectile.h"

Projectile create_projectile(Direction initial_direction, float x, float y) {
    float start_vel_x { 0 };
    float start_vel_y { 0 };

    switch (initial_direction) {
        case Direction::up: {
            start_vel_y = -1;
            break;
        }
        case Direction::down: {
            start_vel_y = 1;
            break;
        }
        case Direction::left: {
            start_vel_x = -1;
            break;
        }
        case Direction::right: {
            start_vel_x = 1;
            break;
        }
    }
    return {
        .body = {
            .x = x,
            .y = y,
            .w = 10,
            .h = 10,
        },
        .velocity = {
            .x = start_vel_x,
            .y = start_vel_y,
        },
    };
}

void update_projectiles(Projectiles& projectiles) {
    for (auto& proj : projectiles) {
        proj.body.x += proj.velocity.x;
        proj.body.y += proj.velocity.y;
    }
}

void draw_projectile(Projectiles& projectiles, SDL_Renderer* renderer) {
    for (auto proj : projectiles) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &proj.body);
    }
}
