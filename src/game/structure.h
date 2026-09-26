#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

struct Part {
    SDL_FRect body;
    int hitpoints;
};

class Structure {
    int hitpoints;

public:
    SDL_FRect body;
    std::vector<Part> parts;

    Structure(SDL_FRect& game_frame, SDL_FRect body);

    void draw(SDL_Renderer* renderer);
};

void draw_all_structures(SDL_Renderer* renderer, std::vector<Structure>& structures);

#endif
