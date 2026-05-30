#ifndef GAME_H
#define GAME_H

#include "game/ship.h"

struct Game {
    Ship player;
    bool running;
};

#endif
