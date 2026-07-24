#include "enemy_grid.h"

#include <iostream>
#include <string>
#include <array>
#include <cctype>

#include <SDL3/SDL_log.h>

#include "grunt.h"
#include <engine/io/reader.h>
#include <game/config.h>

GruntGrid parse_grid_layout(std::string& content) {
    GruntGrid grid {};

    enemy_col_amount;
    enemy_row_amount;

    // enemy_row_amount are also the amount of '|' which are not part of the array.
    if (content.length() - enemy_row_amount != enemy_col_amount * enemy_row_amount) {
	SDL_LogError(0, "content.length = %i, is of the wrong size.", content.length());
	std::exit(1);
    }

    int row = 0;
    for (int i = 0; i < content.length(); ++i) {
	char c = content[i];
	switch (c) {
	case ' ': {
	  break;
	}
	// Note: newlines are not found because it is read into a string without newlines.
	case '|':
	case '\n': {
	  ++row;
	  break;
	}
	default: {
	    if (std::isdigit(c)) {
		// TODO: use a different enemy template based on this number (digit c).
		int hitpoints = 1; 
		auto grunt = Grunt(hitpoints);
		grid[row][i % enemy_col_amount] = grunt;
	    }
	}
	}
    }
    return grid;
}

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height,
    std::string file_path
) {
    GruntGrid grid = {};

    if (file_path.length() > 0) {
	auto content = fs::read_to_string(file_path);
	grid = parse_grid_layout(content);
    } else {
	const unsigned int grunt_amount = 30;
	for (unsigned int i = 0; i < grunt_amount; ++i) {
	    grid[i / 32][i] = Grunt(1);
	}
    }

    const float slice_amount = 9;
    float slice = world_width / slice_amount;

    return {
	.body = {
	    .x = slice,
	    .y = 0,
	    .w = slice * (slice_amount - 2),
	    .h = world_height / 2,
	},
	.direction = Direction::right,
	.enemies = grid,
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

    float horizontal_chunk_size = enemy_grid.body.w / enemy_col_amount;
    float vertical_chunk_size = enemy_grid.body.h / enemy_row_amount;

    unsigned int eb_i = 0;

    for (unsigned int i = 0; i < enemy_grid.enemies.size(); ++i) {
	auto& enemies = enemy_grid.enemies[i];
	for (unsigned int j = 0; j < enemies.size(); ++j) {
	    auto& enemy = enemies[j];
	    if (enemy.hitpoints > 0) {
		enemy_grid.enemy_bodies[eb_i] = {
		    .x = enemy_grid.body.x + j * horizontal_chunk_size,
		    .y = enemy_grid.body.y + i * vertical_chunk_size,
		    .w = horizontal_chunk_size,
		    .h = vertical_chunk_size,
		};
		++eb_i;
	    }
	}
    }
}
