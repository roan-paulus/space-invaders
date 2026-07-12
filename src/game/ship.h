#ifndef SHIP_H
#define SHIP_H

#include "event.h"
#include "window_constants.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <vector>

// Player start variables.
constexpr float width       = 30;
constexpr float start_pos_x = WINDOW_WIDTH / 2 - width / 2;
constexpr float start_pos_y = WINDOW_HEIGHT / 8 * 7;

struct Ship {
    SDL_FRect body {};

    void handle_input(SDL_Event* event) {}
    // void update {}
    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &body);
    }
};

Ship create_ship();

#endif
