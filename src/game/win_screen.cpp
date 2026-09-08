#include "win_screen.h"

#include <string>

namespace WinScreen {

void win_screen(SDLContext& ctx, Game& game, SDL_Event& event, WinScreen::Selection& selection) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
            game.running = false;
        }
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.scancode) {
            case SDL_SCANCODE_UP: {
                selection = WinScreen::Selection::Continue;
                break;
            }
            case SDL_SCANCODE_DOWN: {
                selection = WinScreen::Selection::Quit;
                break;
            }
            case SDL_SCANCODE_SPACE: {
                switch (selection) {
		case WinScreen::Selection::Continue: {
                    game.state = State::Game;
                    break;
                }
		case WinScreen::Selection::Quit: {
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


    ctx.text_renderer.draw("You won!", 0, 0);

    std::string score_text = "Score: " + std::to_string(game.score);
    ctx.text_renderer.draw(score_text, 0, 30);

    std::string continue_text = "Continue";
    if (selection == WinScreen::Selection::Continue) {
	continue_text = "> " + continue_text;
    }
    ctx.text_renderer.draw(continue_text, 100, 0);

    std::string exit_text = "Exit";
    if (selection == WinScreen::Selection::Quit) {
	exit_text = "> " + exit_text;
    }
    ctx.text_renderer.draw(exit_text, 100, 30);
}

}
