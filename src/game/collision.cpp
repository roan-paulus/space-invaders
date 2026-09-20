#include "collision.h"

bool has_collision(SDL_FRect& a, SDL_FRect& b) {
    float a_x2 = a.x + a.w;
    float a_y2 = a.y + a.h;

    float b_x2 = b.x + b.w;
    float b_y2 = b.y + b.h;

    return a.x < b_x2 && a_x2 > b.x
	&& a.y < b_y2 && a_y2 > b.y;
}

bool has_collision(SDL_FRect& a, std::vector<Structure>& structures) {
    for (auto& structure : structures) {
	const auto& b = structure.body;

	float a_x2 = a.x + a.w;
	float a_y2 = a.y + a.h;

	float b_x2 = b.x + b.w;
	float b_y2 = b.y + b.h;

	if (a.x < b_x2 && a_x2 > b.x
	    && a.y < b_y2 && a_y2 > b.y) {
	    return true;
	}
    }
    return false;
}
