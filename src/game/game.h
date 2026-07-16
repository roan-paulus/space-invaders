#ifndef GAME_H
#define GAME_H

#include <game/ship.h>
#include <game/enemy.h>
#include <vector>
#include <SDL3/SDL_rect.h>
#include <game/projectile.h>
#include <engine/ui/frame.h>
#include <game/state.h>

struct Game {
    Ship player;
    EnemyGrid enemy_grid;
    std::vector<Projectile> projectiles;
    bool running;
    Frame frame;
    State state;
};

#endif
