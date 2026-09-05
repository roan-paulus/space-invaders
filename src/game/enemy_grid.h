#pragma once

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
#include <game/projectile.h>
#include <game/resource.h>

using GruntGrid = std::array<Grunts, enemy_row_amount>;

constexpr int body_amount = enemy_col_amount * enemy_row_amount;

struct EnemyGrid {
    SDL_FRect body;
    Direction direction;
    GruntGrid enemies;
    GameTimer timer;

    void draw(SDL_Renderer* renderer);
};

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height,
    float x,
    std::string file_path,
    Resources& resources
);
