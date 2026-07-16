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
	.direction = Direction::right,
	.grunts = grunts,
    };
}

void update_enemy_grid(EnemyGrid& enemy_grid, int window_width, int window_heigth) {
    const bool touched_right_side_screen_boundary =
	enemy_grid.body.x + enemy_grid.body.w >= window_width;

    float step = 10;

    if (touched_right_side_screen_boundary) {
	enemy_grid.direction = Direction::left;
	enemy_grid.body.y += step;
    } else if (enemy_grid.body.x <= 0) {
	enemy_grid.direction = Direction::right;
	enemy_grid.body.y += step;
    }

    switch (enemy_grid.direction) {
    case Direction::left: {
	enemy_grid.body.x -= 1;
	break;
    }
    case Direction::right: {
	enemy_grid.body.x += 1;
	break;
    }
    }

    for (unsigned int i; i < enemy_grid.grunts.size(); ++i) {
	Grunt grunt = enemy_grid.grunts[i];
	grunt.body.x = i * grunt.body.w;
	grunt.body.y = 0;
    }
}
