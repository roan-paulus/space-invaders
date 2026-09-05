#ifndef UI_H
#define UI_H

#include <string>
#include <array>

#include <SDL3/SDL_render.h>

#include "engine/init.h"
#include "window_constants.h"

const size_t UITYPE_AMOUNT = 6;
const size_t UI_AREAS = 2;

enum class WidgetType {
    Score_1,
    Hiscore,
    Score_2,
    Lives,
    Credit,
};

enum class Position {
    Right,
    Left,
};

using Widgets = std::array<WidgetType, UITYPE_AMOUNT / UI_AREAS>;

struct UI {
    SDL_FRect body;
    Widgets widgets;

    UI(Widgets widgets, Position pos, SDL_FRect body)
    : widgets{widgets}
    , body{body}
    {
        if (pos == Position::Left) {
            body.y = 0;
        } else {
            body.y = WINDOW_HEIGHT - WINDOW_HEIGHT / 7.0f;
        }
    }

    void draw(SDLContext& ctx, int score) {
        // Draw the box arround the whole UI Area.
        SDL_RenderRect(ctx.renderer, &this->body);

        for (int i = 0; i < this->widgets.size(); ++i) {
            const WidgetType w = this->widgets[i];
            draw_widget(ctx, w, i, score);
        }
    }

private:
    void draw_widget(SDLContext& ctx, WidgetType widget, int ui_position, int score) {
        switch (widget) {
        case WidgetType::Score_1: {
            std::string text = "Score<1>";
            ctx.text_renderer.draw(text, 10, 10);
            std::string score_text = std::to_string(score);
            ctx.text_renderer.draw(score_text, 10, 30);
            break;
        }
        case WidgetType::Hiscore: {
            std::string text = "Hiscore";
            ctx.text_renderer.draw(text, 10, 50);
            break;
        }
        case WidgetType::Score_2: {
            std::string text = "Score<2>";
            ctx.text_renderer.draw(text, 10, 70);
            break;
        }
        case WidgetType::Lives: {
            std::string text = "Lives";
            ctx.text_renderer.draw(text, WINDOW_WIDTH - 70, 10);
            break;
        }
        case WidgetType::Credit: {
            std::string text = "Credit 00";
            ctx.text_renderer.draw(text, WINDOW_WIDTH - 70, 30);
            break;
        }
        }
    }
};

#endif
