#include "handle.h"

void handle_key_down(SDL_Scancode scancode, Game& game) {
    switch (scancode) {
    case SDL_SCANCODE_Q: {
        game.running = false;
    }
    }
}

void handle(SDL_Event* event, Game& game) {
    switch (event->type) {
    case SDL_EVENT_QUIT: {
        game.running = false;
    }
    case SDL_EVENT_KEY_DOWN: {
        handle_key_down(event->key.scancode, game);
    }
    }
}
