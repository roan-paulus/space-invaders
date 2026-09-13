#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

#include "game/game.h"
#include <engine/init.h>

namespace DeathScreen {

enum class Selection {
    Continue,
    Quit
};

void show(SDLContext& ctx, Game& game, Resources& resources, SDL_Event& event, DeathScreen::Selection& selection);

}

#endif
