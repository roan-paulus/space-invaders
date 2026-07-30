#pragma once

#include "enemy_grid.h"

#include <array>
#include <string>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

#include "grunt.h"
#include <engine/physics/direction.h>
#include <game/config.h>
#include <game/timer.h>
#include <game/animation.h>

using GruntGrid = std::array<Grunts, enemy_row_amount>;

constexpr int body_amount = enemy_col_amount * enemy_row_amount;

struct EnemyGrid {
    SDL_FRect body;
    Direction direction;
    GruntGrid enemies;
    std::array<SDL_FRect, body_amount> enemy_bodies;
    GameTimer timer;
    Animation animation;

    void draw(SDL_Renderer* renderer);
};

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height,
    std::string file_path,
    SDL_Texture* enemy_texture
);

void update_enemy_grid(EnemyGrid& enemy_grid, int window_width, int window_heigth, float delta_time);
