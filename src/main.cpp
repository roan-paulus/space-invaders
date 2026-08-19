#include <cmath>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "event/handle.h"
#include "game/game.h"
#include "window_constants.h"
#include <engine/init.h>
#include <engine/texture.h>
#include <game/enemy_grid.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <game/state.h>
#include <game/start_screen.h>
#include <game/projectile.h>

// Player start variables.
constexpr float width       = 30;
constexpr float start_pos_x = WINDOW_WIDTH / 2 - width / 2;
constexpr float start_pos_y = WINDOW_HEIGHT / 8 * 7;

void main_game_loop(SDLContext& ctx, Game& game, SDL_Event& event, float delta_time);
void assert(bool is_true, const char* message);
void assert_startup_state();

int main(int argc, char** argv) {
    SDLContext ctx;
    initialize_sdl(&ctx, "Space Invaders", WINDOW_WIDTH, WINDOW_HEIGHT);

    TextureLoader texture_loader{ ctx.renderer };
    SDL_Texture* enemy_birdie_texture{ texture_loader.load("assets/enemy_birdie.png") };
    SDL_Texture* player_texture{ texture_loader.load("assets/player_bird.png") };
    SDL_Texture* bullet_texture{ texture_loader.load("assets/bullet.png") };

    Game game = {
        .player = {
            .body = {
                .x = start_pos_x,
                .y = start_pos_y,
                .w = width,
                .h = width,
            },
            .velocity = {
                .x = 100,
                .y = 0,
           },
           .animation{
               .frame_amount{ 3 },
               .frame{ 0 },
               .texture{ player_texture },
               .frame_body{
                   .x{ 0 },
                   .y{ 0 },
                   .w{ 32 },
                   .h{ 32 },
               },
           },
        },
        .enemy_grid  = create_enemy_grid(WINDOW_WIDTH, WINDOW_HEIGHT, "level_1", enemy_birdie_texture),
        .projectiles = {},
        .bullet_texture = bullet_texture,
        .running     = true,
        .frame       {},
        .state       = State::Start,
    };

    Uint64 last_time_ms{0};
    Uint64 current_time_ms{};

    StartScreenState start_screen_state = {
        .selection = Selection::Start,
    };
    SDL_Event event;

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
        case State::Game: {
            main_game_loop(ctx, game, event, delta_time);
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
    SDL_DestroyTexture(enemy_birdie_texture);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(bullet_texture);
    cleanup(&ctx);
    return 0;
}

void main_game_loop(SDLContext& ctx, Game& game, SDL_Event& event, float delta_time) {
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

    int w, h;
    SDL_GetWindowSizeInPixels(ctx.window, &w, &h);
    update_enemy_grid(game.enemy_grid, w, h, delta_time);

    game.enemy_grid.draw(ctx.renderer);
    draw_projectile(game.projectiles, ctx.renderer);
    game.player.draw(ctx.renderer);
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

