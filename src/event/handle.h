#ifndef HANDLE_H
#define HANDLE_H

#include <SDL3/SDL_events.h>
#include <game/game.h>

void handle_key_down(SDL_Scancode scancode, Game& game);

void handle(SDL_Event* event, Game& game);

#endif
