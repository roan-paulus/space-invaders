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

#include "event/handle.h"
#include "game/game.h"
#include "window_constants.h"
#include <engine/init.h>
#include <game/enemy.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <game/state.h>

void assert(bool expression, const char* message) {
    if (expression) {
        return;
    }
    std::cout << "Assertion Error: " << message << std::endl;
    std::exit(1);
}

const bool render_fps = false;

enum class Selection {
    Start = 0,
    Exit = 1,
};

struct StartScreenState {
    Selection selection;
};

void start_screen(SDLContext& ctx, Game& game, SDL_Event& event, StartScreenState& state) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
            game.running = false;
        }
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.scancode) {
            case SDL_SCANCODE_UP: {
                state.selection = Selection::Start;
                break;
            }
            case SDL_SCANCODE_DOWN: {
                state.selection = Selection::Exit;
                break;
            }
            case SDL_SCANCODE_SPACE: {
                switch (state.selection) {
                case Selection::Start: {
                    game.state = State::Game;
                    break;
                }
                case Selection::Exit: {
                    game.running = false;
                    break;
                }
                }
                break;
            }
            }
        }
        }
    }

    std::vector<std::string> options {
        "Start game", "Exit game"
    };

    const int parts = 20;
    std::string a = "Space Invaders";
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    ctx.text_renderer.draw(a, w / 2 - a.length(), h / parts * 1);

    for (unsigned int i; i < options.size(); ++i) {
        std::string& text = options[i];
        if ((unsigned int)state.selection == i) {
            text.insert(0, "> ");
        }
        ctx.text_renderer.draw(text, w / 2 - text.length(), h / parts * (10 + i));
    }
}

void main_game_loop(SDLContext& ctx, Game& game, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        handle(&event, game);
    }
    update_projectiles(game.projectiles);

    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    update_enemy_grid(game.enemy_grid, w, h);

    draw_projectile(game.projectiles, ctx.renderer);
    game.player.draw(ctx.renderer);
    SDL_RenderRect(ctx.renderer, &game.enemy_grid.body);
}

void game_loop(SDLContext& ctx, Game& game) {
    Uint64 last_time_ms = 0;
    Uint64 current_time_ms;

    Uint64 frame_count = 0;

    StartScreenState start_screen_state = {
        .selection = Selection::Start,
    };
    SDL_Event event;
    while (game.running) {
        Uint64 start = SDL_GetTicks();

        SDL_RenderClear(ctx.renderer);

        switch (game.state) {
        case State::Start: {
            start_screen(ctx, game, event, start_screen_state);
            break;
        }
        case State::Game: {
            main_game_loop(ctx, game, event);
            break;
        }
        }

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0);
        SDL_RenderPresent(ctx.renderer);

        current_time_ms = SDL_GetTicks();

        // Log FPS every second:
        if (render_fps && current_time_ms > last_time_ms + 1000) {
            SDL_Log("FPS %i\n", frame_count);
            last_time_ms = current_time_ms;
            frame_count  = 0;
        }

        frame_count += 1;
        Uint64 end               = SDL_GetTicks();
        float elapsed_frame_time = (float)end - (float)start;
        SDL_Delay(
            std::floor(16.666f - elapsed_frame_time)
        ); // CAP FPS: Prevent CPU from going full throttle.
    }
}

void assert_startup_state() {
    // 1920x1080 = fullscreen
    const int aspect_ratio_width  = 16;
    const int aspect_ratio_height = 9;
    assert(WINDOW_WIDTH % aspect_ratio_width == 0, "WINDOW_WIDTH is wrong");
    assert(WINDOW_HEIGHT % aspect_ratio_height == 0, "WINDOW_HEIGHT is wrong");
}

int main(int argc, char** argv) {
    SDLContext ctx;
    initialize_sdl(&ctx, "Space Invaders", WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game = {
        .player      = create_ship(),
        .enemy_grid  = create_enemy_grid(WINDOW_WIDTH, WINDOW_HEIGHT),
        .projectiles = {},
        .running     = true,
        .frame       {},
        .state       = State::Start,
    };
    game_loop(ctx, game);
    SDL_Log("Exiting Game.\n");
    SDL_Quit();
    return 0;
}
