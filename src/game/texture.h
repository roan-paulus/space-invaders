#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL3/SDL_render.h"

struct Texture {
    SDL_Texture* texture;
    SDL_FRect frame;
};

#endif
