#include "structure.h"

Structure::Structure(SDL_FRect& game_frame, SDL_FRect body)
: body{ 
    .x = game_frame.x + body.x, .y = game_frame.y + body.y,
    .w = body.w, .h = body.h,
}
, hitpoints{ 8 }
{}

void Structure::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &body);
    SDL_RenderRect(renderer, &body);
}

void draw_all_structures(SDL_Renderer* renderer, std::vector<Structure>& structures) {
    for (auto& structure : structures) {
	structure.draw(renderer);
    }
}
