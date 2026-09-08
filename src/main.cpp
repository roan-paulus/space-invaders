#include <cmath>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "event/handle.h"
#include "game/game.h"
#include "game/ui.h"
#include "game/update_enemy_grid.h"
#include "window_constants.h"
#include <engine/init.h>
#include <engine/texture.h>
#include <game/enemy_grid.h>
#include <iostream>

#include <game/state.h>
#include <game/start_screen.h>
#include <game/win_screen.h>
#include <game/projectile.h>
#include <game/resource.h>

// Player start variables.
constexpr float width       = 60;
constexpr float height      = 30;
constexpr float start_pos_x = WINDOW_WIDTH / 2.0f - width / 2;
constexpr float start_pos_y = WINDOW_HEIGHT / 8.0f * 7;

void main_game_loop(
    SDLContext& ctx,
    Game& game,
    Resources resources,
    SDL_Event& event,
    float delta_time
);
void assert(bool is_true, const char* message);
void assert_startup_state();

void disribute_window_frame(SDL_FRect& frame) {
    static float used_width_px = 0;

    frame.x = used_width_px;
    frame.y = 0;
    frame.w = WINDOW_WIDTH * frame.w;
    frame.h = WINDOW_HEIGHT;

    used_width_px += frame.w;

    // Height is not supported.
    if (used_width_px <= 1.0f && frame.h != 0) {
        SDL_LogError(0, "Elements cannot be distributed");
        std::exit(1);
    }
}

int main(int argc, char** argv) {
    SDLContext ctx;
    initialize_sdl(&ctx, "Space Invaders", WINDOW_WIDTH, WINDOW_HEIGHT);

    TextureLoader texture_loader{ ctx.renderer };

    const SDL_FRect enemy_texture_default = {
        .x = 0,
        .y = 0,
        .w = 40,
        .h = 32,
    };

    Resources resources = {
        .player = {
            texture_loader.load("assets/player.png"),
            { .x = 0, .y = 0, .w = width, .h = height },
        },
        .red = {
            texture_loader.load("assets/red.png"),
            enemy_texture_default,
        },
        .yellow = {
            texture_loader.load("assets/yellow.png"),
            enemy_texture_default,
        },
        .green = {
            texture_loader.load("assets/green.png"),
            enemy_texture_default,
        },
        .explosion = {
            4,
            1,
            texture_loader.load("assets/explosion.png"),
            { .x = 0, .y = 0, .w = 64, .h = 64 },
            0.07
        },
    };

    // Input '.w' is used as a percentage of the full screen width.
    SDL_FRect ui_left_rect  { .w = 0.15 };
    SDL_FRect game_frame    { .w = 0.7 };
    SDL_FRect ui_right_rect { .w = 0.15 };
    disribute_window_frame(ui_left_rect);
    disribute_window_frame(game_frame);
    disribute_window_frame(ui_right_rect);

    Game game = {
        .player = {
            .body = {
                .x = start_pos_x,
                .y = start_pos_y,
                .w = width,
                .h = height,
            },
            .velocity = {
                .x = 100,
                .y = 0,
            },
            .texture = &resources.player,
        },
        .enemy_grid = create_enemy_grid(
            game_frame.w,
            game_frame.h,
            game_frame.x,
            "level_1",
            resources
        ),
        .projectiles = {},
        .running = true,
        .level = 1,
        .state = State::Game,
        .score = 0,
        .animation_queue = {},
        .game_area = game_frame,
        .left_ui = {
            { WidgetType::Score_1, WidgetType::Hiscore, WidgetType::Score_2, },
            Position::Left,
            ui_left_rect,
        },
        .right_ui = {
            { WidgetType::Lives, WidgetType::Credit, },
            Position::Right,
            ui_right_rect,
        },
    };

    Uint64 last_time_ms{0};
    Uint64 current_time_ms{};

    StartScreenState start_screen_state = {
        .selection = Selection::Start,
    };
    SDL_Event event;
    WinScreen::Selection winscreen_selection = WinScreen::Selection::Continue;

    while (game.running) {
        current_time_ms = SDL_GetTicks();
        float delta_time{ (current_time_ms - last_time_ms) / 1000.0f };
        last_time_ms = current_time_ms;

        SDL_RenderClear(ctx.renderer);

        switch (game.state) {
        case State::Start: {
            start_screen(ctx, game, event, start_screen_state);
            break;
        }
        case State::Win: {
            WinScreen::win_screen(ctx, game, event, winscreen_selection);
            break;
        }
        case State::Game: {
            main_game_loop(ctx, game, resources, event, delta_time);
            break;
        }
        }

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0);
        SDL_RenderPresent(ctx.renderer);

        Uint64 loop_duration_ms{ SDL_GetTicks() - current_time_ms };

        constexpr Uint64 desired_loop_duration_ms = 8;
        // Prevent overflow.
        if (loop_duration_ms <= desired_loop_duration_ms) {
            // Cap compute to prevent CPU going like brrrrrrrrr. TODO: Use sdl vsync?
            SDL_Delay(desired_loop_duration_ms - loop_duration_ms);
        }
    }

    SDL_Log("Exiting Game.\n");

    SDL_DestroyTexture(resources.player.texture);
    SDL_DestroyTexture(resources.red.texture);
    SDL_DestroyTexture(resources.green.texture);
    SDL_DestroyTexture(resources.yellow.texture);
    SDL_DestroyTexture(resources.explosion.texture);
    cleanup(&ctx);
    return 0;
}

void main_game_loop(
    SDLContext& ctx,
    Game& game,
    Resources resources,
    SDL_Event& event,
    float delta_time
) {
    while (SDL_PollEvent(&event)) {
        handle(&event, game, delta_time);
    }

    const bool* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_LEFT]) {
        game.player.body.x -= game.player.velocity.x * delta_time;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        game.player.body.x += game.player.velocity.x * delta_time;
    }

    update_projectiles(game.projectiles, delta_time);

    update_enemy_grid(game, delta_time, resources);

    for (auto& obj : game.animation_queue) {
        obj.animation.step(delta_time);
        obj.animation.draw(ctx.renderer, &obj.location);
    }

    game.animation_queue.erase(
        std::remove_if(
            game.animation_queue.begin(), game.animation_queue.end(),
            [](auto ao) {
                return ao.animation.is_at_end();
            }
        ),
        game.animation_queue.end()
    );

    game.left_ui.draw(ctx, game.score);
    game.right_ui.draw(ctx, game.score);
    game.enemy_grid.draw(ctx.renderer);
    draw_projectile(game.projectiles, ctx.renderer);
    game.player.draw(ctx.renderer);

    // Winning condition check:
    bool found_one_alive = false;
    for (auto& row : game.enemy_grid.enemies) {
        for (auto& enemy : row) {
            if (enemy.hitpoints > 0) {
                found_one_alive = true;
                goto end_enemy_check;
            }
        }
    }
end_enemy_check:
    if (!found_one_alive) {
        ++game.level;
        game.state = State::Win;
        game.enemy_grid = create_enemy_grid(game.game_area.w, game.game_area.h, game.game_area.x, "level_" + std::to_string(game.level), resources);
    }
    return;
}

void assert(bool is_true, const char* message) {
    if (is_true) {
        return;
    }
    std::cout << "Assertion Error: " << message << std::endl;
    std::exit(1);
}

void assert_startup_state() {
    // 1920x1080 = fullscreen
    const int aspect_ratio_width  = 16;
    const int aspect_ratio_height = 9;
    assert(WINDOW_WIDTH % aspect_ratio_width == 0, "WINDOW_WIDTH is wrong");
    assert(WINDOW_HEIGHT % aspect_ratio_height == 0, "WINDOW_HEIGHT is wrong");
}

