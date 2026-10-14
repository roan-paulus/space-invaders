#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include <utility>

struct TextRenderer {
    TTF_TextEngine* text_engine;
    TTF_Font* font;

    std::pair<int, int> get_string_size(const std::string& text) {
        int w;
        int h;
        TTF_GetStringSize(font, text.c_str(), text.length(), &w, &h);
        return { w, h };
    }

    float get_font_size() {
        return TTF_GetFontSize(font);
    }

    void set_font_size(float new_size) {
        TTF_SetFontSize(font, new_size);
    }

    void draw(const std::string& text, const float x, const float y) {
        TTF_Text* ttf_text = TTF_CreateText(text_engine, font, text.c_str(), text.length());
        TTF_DrawRendererText(ttf_text, x, y);
        TTF_DestroyText(ttf_text);
    }

    void draw_centered(const std::string& text, const float x, const float y) {
        auto s = get_string_size(text);
        auto& width = s.first;
        auto& heigth = s.second;

        draw(text, x - static_cast<float>(width) / 2, y - static_cast<float>(heigth) / 2);
    }
};

#endif
