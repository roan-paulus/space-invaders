#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL3/SDL_rect.h>

#include <game/ship.h>
#include <game/enemy_grid.h>
#include <game/projectile.h>
#include <game/state.h>
#include <game/resource.h>
#include <game/animation.h>
#include <game/ui.h>
#include <game/structure.h>
#include <game/ufo.h>

struct Game {
    Player player;
    std::vector<Structure> structures;
    EnemyGrid enemy_grid;
    UFOSpawner UFO_spawner;
    std::vector<Projectile> projectiles;
    bool running;
    int level;
    State state;
    std::vector<AnimationObject> animation_queue;
    SDL_FRect game_area;
    UI left_ui;
    UI right_ui;

    Game(
        Resources& resources,
        SDL_FRect& game_frame,
        SDL_FRect& ui_left_rect,
        SDL_FRect& ui_right_rect,
        int score = 0,
        int lives = 3
    )
    : player{
        .body = {
            .x = Player::start_pos_x,
            .y = Player::start_pos_y,
            .w = Player::width,
            .h = Player::height,
        },
        .velocity = {
            .x = 100,
            .y = 0,
        },
        .lives = lives,
        .texture = &resources.player,
        .shooting = false,
        .score = score,
    }
    , structures{ initialize_structures(game_frame) }
    , enemy_grid{ create_enemy_grid(
            game_frame.w,
            game_frame.h,
            game_frame.x,
            "level_1",
            resources
    )}
    , UFO_spawner{ &resources.ufo, &game_frame }
    , projectiles{ {} }
    , running{ true }
    , level{ 1 }
    , state{ State::Game }
    , animation_queue{ {} }
    , game_area{ game_frame }
    , left_ui{
        { WidgetType::Score_1, WidgetType::Hiscore, WidgetType::Score_2, },
        Position::Left,
        ui_left_rect,
    }
    , right_ui{
        { WidgetType::Lives, WidgetType::Credit, },
        Position::Right,
        ui_right_rect,
    }
    {}
};

#endif
