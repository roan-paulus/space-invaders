#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "game/game.h"
#include <engine/init.h>

namespace WinScreen {

enum class Selection {
    Continue,
    Quit
};

void win_screen(SDLContext& ctx, Game& game, SDL_Event& event, WinScreen::Selection& selection);

}

#endif
