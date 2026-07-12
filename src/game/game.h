#ifndef GAME_H
#define GAME_H

#include <game/ship.h>
#include <game/enemy.h>
#include <vector>
#include <SDL3/SDL_rect.h>
#include <game/projectile.h>

struct Game {
    Ship player;
    EnemyGrid enemy_grid;
    std::vector<Projectile> projectiles;
    bool running;
};

#endif
