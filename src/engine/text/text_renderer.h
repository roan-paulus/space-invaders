#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <SDL3_ttf/SDL_ttf.h>

struct TextRenderer {
    TTF_TextEngine* text_engine;
    TTF_Font* font;

    float get_font_size() {
        return TTF_GetFontSize(font);
    }

    void set_font_size(float new_size) {
        TTF_SetFontSize(font, new_size);
    }

    void draw(const std::string text, const float x, const float y) {
        TTF_Text* ttf_text = TTF_CreateText(text_engine, font, text.c_str(), text.length());
        TTF_DrawRendererText(ttf_text, x, y);
        TTF_DestroyText(ttf_text);
    }
};

#endif
