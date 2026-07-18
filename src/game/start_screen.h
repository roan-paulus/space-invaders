#pragma once

#include "game/game.h"
#include <engine/init.h>

enum class Selection {
    Start = 0,
    Exit = 1,
};

struct StartScreenState {
    Selection selection;
};

void start_screen(SDLContext& ctx, Game& game, SDL_Event& event, StartScreenState& state);
