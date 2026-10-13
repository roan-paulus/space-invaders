#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

#include "game/game.h"
#include <engine/init.h>

namespace DeathScreen {

enum class Selection {
    Continue,
    Quit
};

void handle(SDL_Event& event, Game& game, Resources& resources, DeathScreen::Selection& selection);

void show(SDLContext& ctx, Game& game, Resources& resources, DeathScreen::Selection& selection);

void show_game_over(SDLContext& ctx, Game& game, Resources& resources, DeathScreen::Selection& selection);

}

#endif
