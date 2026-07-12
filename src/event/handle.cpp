#include "handle.h"
#include "game/projectile.h"

void handle_key_down(SDL_Scancode scancode, Game& game) {
    switch (scancode) {
    case SDL_SCANCODE_Q: {
        game.running = false;
        break;
    }
    case SDL_SCANCODE_LEFT: {
        game.player.body.x -= 5;
        break;
    }
    case SDL_SCANCODE_RIGHT: {
        game.player.body.x += 5;
        break;
    }
    case SDL_SCANCODE_SPACE: {
        auto& player = game.player;
        Projectile projectile = create_projectile(
            Direction::up, player.body.x, player.body.y
        );
        // Center the projectile relative to the player size.
        projectile.body.x = (projectile.body.x + player.body.w / 2) - projectile.body.w / 2;
        // Spawn above the player.
        projectile.body.y -= projectile.body.h;
        game.projectiles.push_back(projectile);
        break;
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
