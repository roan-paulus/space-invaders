#include "enemy_grid.h"
#include "game/animation.h"
#include "update_enemy_grid.h"

#include <string>
#include <array>
#include <cctype>

#include <SDL3/SDL_log.h>
#include <SDL3_image/SDL_image.h>

#include "game/game.h"
#include "game/resource.h"
#include "grunt.h"
#include <engine/io/reader.h>
#include <engine/vec2.h>
#include <game/config.h>
#include <game/timer.h>

GruntGrid parse_grid_layout(std::string& content, Resources& resources) {
    GruntGrid grid {};

    // enemy_row_amount are also the amount of '|' which are not part of the array.
    if (content.length() - enemy_row_amount != enemy_col_amount * enemy_row_amount) {
	SDL_LogError(0, "content.length = %zu, is of the wrong size.", content.length());
	std::exit(1);
    }

    int row = 0;
    for (int i = 0; i < content.length(); ++i) {
	char c = content[i];
	Texture* texture { nullptr };
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
		switch (c) {
		case '1': {
		    texture = &resources.red;
		    break;
		}
		case '2': {
		    texture = &resources.green;
		    break;
		}
		case '3': {
		    texture = &resources.yellow;
		    break;
		}
		default: {
		    SDL_LogError(0, "Unknown enemy type");
		}
		}

		int hitpoints = 1;
		SDL_FRect body = {
		    .x = 6
		};
		Grunt grunt { hitpoints, body, texture };

		grid[row][i % enemy_col_amount] = grunt;
	    }
	}
	}
    }
    return grid;
}

const float PADDING_X = 64;
const float PADDING_Y = 64;

EnemyGrid create_enemy_grid(
    float world_width,
    float world_height,
    float x,
    std::string file_path,
    Resources& resources
) {
    GruntGrid grid = {};

    if (file_path.length() > 0) {
	auto content = fs::read_to_string(file_path);
	grid = parse_grid_layout(content, resources);
    } else {
	const unsigned int grunt_amount = 30;
	for (unsigned int i = 0; i < grunt_amount; ++i) {
	    grid[i / 32][i] = Grunt { 1, {}, nullptr };
	}
    }

    const float slice_amount = 9;
    float slice = x + world_width / slice_amount;

    EnemyGrid result{
	.body = {
	    .x = slice,
	    .y = 0,
	    .w = enemy_col_amount * 40 + PADDING_X,
	    .h = enemy_row_amount * 32 + PADDING_Y,
	},
	.direction = Direction::right,
	.enemies = grid,
	.timer = { .length = 1, .timeout = true },
    };
    return result;
}

class Counter {
    int count;

public:
    int limit;

    Counter(int limit = 10, int start_count = 0)
	: count{ start_count }
	, limit{ limit }
    {}

    void tick() {
	++count;
    }

    void reset() {
	count = 0;
    }

    bool limit_reached() {
	return count >= limit;
    }

    int get_count() {
	return count;
    }
};

void update_enemy_grid(
    Game& game,
    int window_width,
    int window_heigth,
    float delta_time,
    Resources& resources
) {
    for (unsigned int i = 0; i < game.enemy_grid.enemies.size(); ++i) {
	auto& enemies = game.enemy_grid.enemies[i];
	for (unsigned int j = 0; j < enemies.size(); ++j) {
	    auto& enemy = enemies[j];
	    // TODO: Remove size check
	    if (enemy.hitpoints == 0 && enemy.enabled && game.animation_queue.size() == 0) {
		++game.score;
		enemy.enabled = false;
		AnimationObject ao = {
		    .animation = resources.explosion,
		    .location = {
			// Subtraction to get to optimal animation position.
			enemy.body.x - 8,
			enemy.body.y - 16,
			64,
			64,
		    }
		};
		game.animation_queue.push_back(ao);
		continue;
	    }
	    for (auto& projectile: game.projectiles) {
		if (enemy.hitpoints > 0 && enemy.has_collision(projectile)) {
		    // Queue for deletion:
		    projectile.out_of_bounds = true;
		    --enemy.hitpoints;
		}
	    }
	}
    }

    if (!game.enemy_grid.timer.isTimeoutAndStep(delta_time)) {
	return;
    }

    const int limit = 10;
    static Counter counter { limit };

    if (counter.limit_reached()) {
	game.enemy_grid.timer.length -= 0.1;
	counter.reset();
	counter.limit += 1;
    }
    counter.tick();

    const bool touched_right_side_screen_boundary =
	game.enemy_grid.body.x + game.enemy_grid.body.w >= game.game_area.x + game.game_area.w;

    Vec2 velocity = {
	.x = 15,
	.y = 15,
    };

    if (touched_right_side_screen_boundary) {
	game.enemy_grid.direction = Direction::left;
	game.enemy_grid.body.y += velocity.y;
    } else if (game.enemy_grid.body.x <= game.game_area.x) {
	game.enemy_grid.direction = Direction::right;
	game.enemy_grid.body.y += velocity.y;
    }

    switch (game.enemy_grid.direction) {
    case Direction::left: {
	game.enemy_grid.body.x -= velocity.x;
	break;
    }
    case Direction::right: {
	game.enemy_grid.body.x += velocity.x;
	break;
    }
    case Direction::up:
    case Direction::down:
	SDL_LogError(0, "Grid is not supposed to change directions to up or down");
        break;
    }

    float horizontal_chunk_size = game.enemy_grid.body.w / enemy_col_amount;
    float vertical_chunk_size = game.enemy_grid.body.h / enemy_row_amount;

    float padding_x = PADDING_X / 11;
    float padding_y = PADDING_Y / 11;

    for (unsigned int i = 0; i < game.enemy_grid.enemies.size(); ++i) {
	auto& enemies = game.enemy_grid.enemies[i];
	for (unsigned int j = 0; j < enemies.size(); ++j) {
	    auto& enemy = enemies[j];

	    if (enemy.hitpoints > 0) {
		enemy.body = {
		    .x = game.enemy_grid.body.x + j * horizontal_chunk_size + j * padding_x,
		    .y = game.enemy_grid.body.y + i * vertical_chunk_size + i * padding_y,
		    .w = 40,
		    .h = 32,
		};
	    }
	}
    }
}

void EnemyGrid::draw(SDL_Renderer* renderer) {
    for (auto& rows: enemies) {
	for (auto& enemy: rows) {
	    if (enemy.hitpoints > 0) {
		enemy.draw(renderer, enemy.texture->frame);
	    }
	}
    }
}
