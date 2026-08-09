#include <engine/vec2.h>
#include <SDL3_image/SDL_image.h>

struct GameObject {
    Vec2 body;
    SDL_Texture* texture;
};
