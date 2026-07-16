#include "enemy.h"
#include <iostream>

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height
) {
    const float slice_amount = 9;
    float slice = world_width / slice_amount;

    SDL_FRect enemy_grid {
	.x = slice,
	.y = 0,
	.w = slice * (slice_amount - 2),
	.h = world_height / 2,
    };

    std::vector<Grunt> grunts = {};

    const unsigned int grunt_amount = 10;
    for (unsigned int i; i < grunt_amount; ++i) {
	grunts.push_back(Grunt());
    }

    return {
	.body = enemy_grid,
	.grunts = grunts,
    };
}

void update_enemy_grid(EnemyGrid& enemy_grid, int window_width, int window_heigth) {
    // TODO: this can't be it keeps getting called per loop, so this function does not remeber any state.
    float add = 1;
    if (enemy_grid.body.x + enemy_grid.body.w >= window_width || enemy_grid.body.x <= 0) {
	add * -1;
    }
    enemy_grid.body.x += add;
    float row = 1;
    for (unsigned int i; i < enemy_grid.grunts.size(); ++i) {
	Grunt grunt = enemy_grid.grunts[i];
	grunt.body.x = i * grunt.body.w;
	grunt.body.y = row;
    }
}
