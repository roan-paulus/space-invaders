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

    return {
	.body = enemy_grid,
	.grunts = {},
    };
}
