#ifndef GAME_H
#define GAME_H

#include <game/ship.h>
#include <game/enemy_grid.h>
#include <vector>
#include <SDL3/SDL_rect.h>
#include <game/projectile.h>
#include <engine/ui/frame.h>
#include <game/state.h>

struct Game {
    Ship player;
    EnemyGrid enemy_grid;
    std::vector<Projectile> projectiles;
    SDL_Texture* bullet_texture;
    bool running;
    Frame frame;
    State state;
};

#endif
