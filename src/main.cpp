#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>

#include "engine/init.h"

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char** argv) {
    engine::Init engine("Hello", WINDOW_WIDTH, WINDOW_HEIGHT);

    bool keep_playing {true};
    while (keep_playing) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                goto end_while;
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_Q) {
                    goto end_while;
                }
            }
        }

        const double now = ((double)SDL_GetTicks()) / 1000.0;

        const float red = (float)(0.5 + 0.5 * SDL_sin(now));
        const float green =
            (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

        SDL_SetRenderDrawColorFloat(
            engine.renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT
        );
        SDL_RenderClear(engine.renderer);
        SDL_RenderPresent(engine.renderer);
    }
end_while:
    SDL_Log("Hello world\n");
    return 0;
}
