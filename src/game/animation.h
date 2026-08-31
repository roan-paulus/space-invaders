#ifndef GAME_ANIMATION
#define GAME_ANIMATION

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <game/timer.h>
#include <iostream>

class Animation {
    int cols;
    int rows;
    SDL_FRect frame_body;
    GameTimer timer;

public:
    SDL_Texture* texture;
    int frame_col;
    int frame_row;

    Animation(int cols, int rows, SDL_Texture* texture, SDL_FRect frame_body, float timer_length)
        : cols{ cols - 1 }
        , rows{ rows - 1 }
        , frame_col{ 0 }
        , frame_row{ 0 }
        , texture{ texture }
        , frame_body{ frame_body }
        , timer { timer_length }
    {}

    void step(float delta_time) {
        if (timer.isTimeoutAndStep(delta_time)) {
            if (frame_col >= cols) {
                if (frame_row >= rows) {
                    frame_col = 0;
                    frame_row = 0;
                } else {
                    ++frame_row;
                    frame_col = 0;
                }
            } else {
                ++frame_col;
            }
            frame_body.x = frame_col * frame_body.w;
            frame_body.y = frame_col * frame_body.h;
        }
    }

    void draw(SDL_Renderer* renderer, SDL_FRect* to) {
        SDL_RenderTexture(renderer, texture, &frame_body, to);
    }

    bool is_at_end() {
        return frame_col == cols && frame_row == rows;
    }
};

struct AnimationObject {
    Animation animation;
    SDL_FRect location;
};

#endif
