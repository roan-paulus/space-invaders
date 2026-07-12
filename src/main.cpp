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

void assert(bool expression, const char* message) {
    if (expression) {
        return;
    }
    std::cout << "Assertion Error: " << message << std::endl;
    std::exit(1);
}

const bool render_fps = false;

void start_screen(SDLContext& ctx, Game& game, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        handle(&event, game);
    }
    std::string a = "Space Invaders";
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    ctx.text_renderer.draw(a, w / 2 - a.length(), h / 3);

    std::string b = "Start game";
    ctx.text_renderer.draw(b, w / 2 - b.length(), h / 3 * 2);
}

void game_inner_loop(SDLContext& ctx, Game& game, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        handle(&event, game);
    }

    for (auto& proj : game.projectiles) {
        proj.body.x += proj.velocity.x;
        proj.body.y += proj.velocity.y;
    }

    for (auto proj : game.projectiles) {
        SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);
        SDL_RenderRect(ctx.renderer, &proj.body);
    }
    game.player.draw(ctx.renderer);
    SDL_RenderRect(ctx.renderer, &game.enemy_grid.body);
}

void game_loop(SDLContext& ctx, Game& game) {
    Uint64 last_time_ms = 0;
    Uint64 current_time_ms;

    Uint64 frame_count = 0;

    SDL_Event event;
    while (game.running) {
        Uint64 start = SDL_GetTicks();

        SDL_RenderClear(ctx.renderer);

        // game_inner_loop(ctx, game, event);
        start_screen(ctx, game, event);

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
    };
    game_loop(ctx, game);
    SDL_Log("Exiting Game.\n");
    SDL_Quit();
    return 0;
}
