#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>

#include "event/handle.h"
#include "game/game.h"
#include "window_constants.h"
#include <cmath>
#include <engine/init.h>

const bool render_fps = true;

void game_inner_loop(SDLContext& ctx, Game& game, SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        handle(&event, game);
    }
    // TODO: Move the invaders here
    game.player.draw(ctx.renderer);
}

void game_loop(SDLContext& ctx, Game& game) {
    Uint64 last_time_ms = 0;
    Uint64 current_time_ms;

    Uint64 frame_count = 0;

    SDL_Event event;
    while (game.running) {
        Uint64 start = SDL_GetTicks();

        SDL_RenderClear(ctx.renderer);

        game_inner_loop(ctx, game, event);

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0);
        SDL_RenderPresent(ctx.renderer);

        current_time_ms = SDL_GetTicks();

        // Log FPS every second:
        if (current_time_ms > last_time_ms + 1000) {
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

int main(int argc, char** argv) {
    SDLContext ctx;
    initialize_sdl(&ctx, "Space Invaders", WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game = {
        .player  = create_ship(),
        .running = true,
    };
    game_loop(ctx, game);
    SDL_Log("Exiting Game.\n");
    SDL_Quit();
    return 0;
}
