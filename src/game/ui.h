#ifndef UI_H
#define UI_H

#include <SDL3/SDL_render.h>
#include <array>

const size_t UITYPE_AMOUNT = 6;
const size_t UI_AREAS = 2;

enum class UIType {
    Score_1,
    Hiscore,
    Score_2,
    Lives,
    Credit,
};

struct UI {
    SDL_FRect body;
    std::array<UIType, UITYPE_AMOUNT / UI_AREAS> uitype;

    void draw(SDL_Renderer* renderer) {
        for (auto& t : this->uitype) {
            SDL_RenderRect(renderer, &this->body);
        }
    }
};

#endif
