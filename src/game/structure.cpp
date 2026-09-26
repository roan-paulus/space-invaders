#include "structure.h"

Structure::Structure(SDL_FRect& game_frame, SDL_FRect body)
    : body{ 
	.x = game_frame.x + body.x, .y = game_frame.y + body.y,
	.w = body.w, .h = body.h,
    }
    , hitpoints{ 8 }
{
    const int rows{3};
    const int cols{4};

    float part_width  = this->body.w / cols;
    float part_height = this->body.h / rows;

    for (int row{0}; row < rows; ++row) {
	for (int col{0}; col < cols; ++col) {
	    if (row == 2 && col > 0 && col < 3) {
		continue;
	    }
	    this->parts.push_back({
		.body = {
		    .x = this->body.x + part_width  * static_cast<float>(col % cols),
		    .y = this->body.y + part_height * row,
		    .w = part_width,
		    .h = part_height,
		},
		.hitpoints = 4,
	    });
	}
    }
}

void draw_all_structures(SDL_Renderer* renderer, std::vector<Structure>& structures) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto& structure : structures) {
	for (auto& part : structure.parts) {
	    if (part.hitpoints > 0) {
		SDL_RenderRect(renderer, &part.body);
	    }
	}
    }
}
