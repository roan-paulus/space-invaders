#include "death_screen.h"
#include "game/enemy_grid.h"

#include <string>

namespace DeathScreen {

void show(SDLContext& ctx, Game& game, Resources& resources, SDL_Event& event, DeathScreen::Selection& selection) {
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


    ctx.text_renderer.draw("You Died.", 0, 0);

    std::string score_text = "Score: " + std::to_string(game.score);
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

}
