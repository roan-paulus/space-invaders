#pragma once

#include <array>
#include <vector>
#include <string>
#include <random>
#include <chrono>

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
    std::vector<Grunt*> bottom_edge_grunts;
    GameTimer movement_timer;
    GameTimer projectile_timer;
    std::mt19937 rd {
        static_cast<std::mt19937::result_type>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )
    };

    void draw(SDL_Renderer* renderer);
};

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height,
    float x,
    std::string file_path,
    Resources& resources
);
