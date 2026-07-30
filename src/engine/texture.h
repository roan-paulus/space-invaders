#pragma once

#include <string>

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

struct TextureLoader {
    TextureLoader(SDL_Renderer* renderer)
        : renderer{renderer}
    {}

    SDL_Texture* load(std::string path) {
        SDL_Texture* texture { IMG_LoadTexture(renderer, path.c_str()) };
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
        return texture;
    }

private:
    SDL_Renderer* renderer;
};
