#include "handle.h"

#include <SDL3/SDL_keyboard.h>

#include <game/ship.h>

void handle_key_down(SDL_Scancode scancode, Game& game, float delta_time) {
    switch (scancode) {
    case SDL_SCANCODE_Q: {
        game.running = false;
        break;
    }
    case SDL_SCANCODE_SPACE: {
        if (game.player.shooting) {
            break;
        }
        game.player.shoot(game.projectiles);
        break;
    }
    }
}

void handle(SDL_Event* event, Game& game, float delta_time) {
    switch (event->type) {
    case SDL_EVENT_QUIT: {
        game.running = false;
    }
    case SDL_EVENT_KEY_DOWN: {
        handle_key_down(event->key.scancode, game, delta_time);
    }
    }
}
