#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <SDL3/SDL_rect.h>

struct Grunt {
    SDL_FRect body;
    float hitpoints;
};

struct EnemyGrid {
    SDL_FRect body;
    std::vector<Grunt> grunts;
};

EnemyGrid create_enemy_grid(float world_width, float world_height);

#endif
