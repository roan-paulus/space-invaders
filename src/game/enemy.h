#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <SDL3/SDL_rect.h>
#include <engine/physics/direction.h>

struct Grunt {
    SDL_FRect body;
    float hitpoints;

    Grunt() {
        hitpoints = 1;
        body = {
            .x = 0,
            .y = 0,
            .w = 5,
            .h = 5,
        };
    }
};

struct EnemyGrid {
    SDL_FRect body;
    Direction direction;
    std::vector<Grunt> grunts;
};

EnemyGrid create_enemy_grid(float world_width, float world_height);

void update_enemy_grid(EnemyGrid& enemy_grid, int window_width, int window_heigth);

#endif
