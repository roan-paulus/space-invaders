#include "start_screen.h"

void start_screen(SDLContext& ctx, Game& game, SDL_Event& event, StartScreenState& state) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
            game.running = false;
        }
        case SDL_EVENT_KEY_DOWN: {
            switch (event.key.scancode) {
            case SDL_SCANCODE_UP: {
                state.selection = Selection::Start;
                break;
            }
            case SDL_SCANCODE_DOWN: {
                state.selection = Selection::Exit;
                break;
            }
            case SDL_SCANCODE_SPACE: {
                switch (state.selection) {
                case Selection::Start: {
                    game.state = State::Game;
                    break;
                }
                case Selection::Exit: {
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

    std::vector<std::string> options {
        "Start game", "Exit game"
    };

    const int parts = 20;
    std::string a = "Space Invaders";
    int w, h;
    SDL_GetWindowSize(ctx.window, &w, &h);
    ctx.text_renderer.draw(a, w / 2 - a.length(), h / parts * 1);

    for (unsigned int i; i < options.size(); ++i) {
        std::string& text = options[i];
        if ((unsigned int)state.selection == i) {
            text.insert(0, "> ");
        }
        ctx.text_renderer.draw(text, w / 2 - text.length(), h / parts * (10 + i));
    }
}
