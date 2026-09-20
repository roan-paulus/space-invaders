#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include <SDL3/SDL_rect.h>

#include "game/structure.h"

bool has_collision(SDL_FRect& a, SDL_FRect& b);
bool has_collision(SDL_FRect& a, std::vector<Structure>& structures);

#endif
