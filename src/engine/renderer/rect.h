#ifndef RECT_H
#define RECT_H

struct Rect {
    float x;
    float y;
    float width;
    float height;

    SDL_FRect as_SDL_Rect() {
        return {
            .x = x,
            .y = y,
            .w = width,
            .h = height,
        };
    }
};

#endif
