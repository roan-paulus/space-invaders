#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>

#include "scratch.h"
#include "window_constants.h"
#include <init.h>
#include <renderer/renderer.h>

int main(int argc, char** argv) {
    engine::Init engine("Hello", WINDOW_WIDTH, WINDOW_HEIGHT);
    game::World world;

    // Ship player(0, 0, 80, 80);
    while (engine.event.keep_playing) {
        engine.renderer.clear();

        world.player.draw(&engine.renderer);

        // update();
        while (engine.event.poll()) {
            engine.event.handle();
            world.player.handle_input(&engine.event);
        }

        engine.renderer.set_draw_color(0, 0, 0, 0);
        engine.renderer.present();
    }
end_while:
    SDL_Log("Hello world\n");
    return 0;
}
