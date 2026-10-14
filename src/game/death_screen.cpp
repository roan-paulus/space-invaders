#include "death_screen.h"
#include "game/enemy_grid.h"
#include "window_constants.h"

#include <string>

namespace DeathScreen {

void handle(SDL_Event& event, Game& game, Resources& resources, DeathScreen::Selection& selection) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
            game.running = false;
        }
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.scancode) {
            case SDL_SCANCODE_UP: {
                selection = DeathScreen::Selection::Continue;
                break;
            }
            case SDL_SCANCODE_DOWN: {
                selection = DeathScreen::Selection::Quit;
                break;
            }
            case SDL_SCANCODE_SPACE: {
                switch (selection) {
		case DeathScreen::Selection::Continue: {
                    game.state = State::Game;
                    game.enemy_grid = create_enemy_grid(
                        game.game_area.w,
                        game.game_area.h,
                        game.game_area.x,
                        "level_1",
                        resources
                    );
                    game.projectiles = {};
                    break;
                }
		case DeathScreen::Selection::Quit: {
                    game.running = false;
                    break;
                }
                }
                break;
            }
            }
        }
        }
    }
}

void show(SDLContext& ctx, Game& game, Resources& resources, DeathScreen::Selection& selection) {
    ctx.text_renderer.draw("You Died.", 0, 0);

    std::string score_text = "Score: " + std::to_string(game.player.score);
    ctx.text_renderer.draw(score_text, 0, 30);

    std::string continue_text = "Continue";
    if (selection == DeathScreen::Selection::Continue) {
	continue_text = "> " + continue_text;
    }
    ctx.text_renderer.draw(continue_text, 100, 0);

    std::string exit_text = "Exit";
    if (selection == DeathScreen::Selection::Quit) {
	exit_text = "> " + exit_text;
    }
    ctx.text_renderer.draw(exit_text, 100, 30);
}

void show_game_over(SDLContext& ctx, Game& game, Resources& resources, DeathScreen::Selection& selection) {
    auto& tr = ctx.text_renderer;

    float old_size = ctx.text_renderer.get_font_size();
    ctx.text_renderer.set_font_size(64);

    float ww = WINDOW_WIDTH;
    float wh = WINDOW_HEIGHT;
    const float parts_height = 10;

    std::string game_over_text = "Game over";

    tr.draw_centered(game_over_text, ww / 2, wh / parts_height * 3);

    tr.set_font_size(32);
    std::string score_text;
    if (game.player.score > game.player.hiscore) {
        score_text = "New hiscore: " + std::to_string(game.player.score);
    } else {
        score_text = "Final score: " + std::to_string(game.player.score);
    }
    tr.draw_centered(score_text, ww / 2, wh / parts_height * 6);

    tr.set_font_size(old_size);
}

} // DeathScreen
