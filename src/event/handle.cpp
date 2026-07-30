#include "handle.h"

#include <SDL3/SDL_keyboard.h>

#include "game/projectile.h"
#include <game/ship.h>

void handle_key_down(SDL_Scancode scancode, Game& game, float delta_time) {
    switch (scancode) {
    case SDL_SCANCODE_Q: {
        game.running = false;
        break;
    }
    case SDL_SCANCODE_SPACE: {
        auto& player = game.player;
        Projectile projectile = create_projectile(player.body.x, player.body.y);
        // Center the projectile relative to the player size.
        projectile.body.x = (projectile.body.x + player.body.w / 2) - projectile.body.w / 2;
        // Spawn above the player.
        projectile.body.y -= projectile.body.h;
        game.projectiles.push_back(projectile);
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
