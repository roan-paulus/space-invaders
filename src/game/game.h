#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <vector>
#include <SDL3/SDL_rect.h>

#include <game/ship.h>
#include <game/enemy_grid.h>
#include <game/projectile.h>
#include <game/state.h>
#include <game/resource.h>
#include <game/animation.h>
#include <game/ui.h>

struct Game {
    Ship player;
    EnemyGrid enemy_grid;
    std::vector<Projectile> projectiles;
    bool running;
    int level;
    State state;
    int score;
    std::vector<AnimationObject> animation_queue;
    SDL_FRect game_area;
    UI left_ui;
    UI right_ui;
};

#endif
