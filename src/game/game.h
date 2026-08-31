#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL3/SDL_rect.h>

#include <engine/ui/frame.h>
#include <game/ship.h>
#include <game/enemy_grid.h>
#include <game/projectile.h>
#include <game/state.h>
#include <game/resource.h>
#include <game/animation.h>

struct Game {
    Ship player;
    EnemyGrid enemy_grid;
    std::vector<Projectile> projectiles;
    bool running;
    Frame frame;
    State state;
    std::vector<AnimationObject> animation_queue;
};

#endif
