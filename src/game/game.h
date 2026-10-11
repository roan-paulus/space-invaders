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
    Ship player;
    std::vector<Structure> structures;
    EnemyGrid enemy_grid;
    UFOSpawner UFO_spawner;
    std::vector<Projectile> projectiles;
    bool running;
    int level;
    State state;
    int score;
    std::vector<AnimationObject> animation_queue;
    SDL_FRect game_area;
    UI left_ui;
    UI right_ui;

    Game* start_state { nullptr };

    Game(
        Resources& resources,
        SDL_FRect& game_frame,
        SDL_FRect& ui_left_rect,
        SDL_FRect& ui_right_rect
    )
    : player{
        .body = {
            .x = Ship::start_pos_x,
            .y = Ship::start_pos_y,
            .w = Ship::width,
            .h = Ship::height,
        },
        .velocity = {
            .x = 100,
            .y = 0,
        },
        .texture = &resources.player,
        .shooting = false,
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
    , score{ 0 }
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
