#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_render.h>

namespace engine {

class Renderer {
  public:
    Renderer(SDL_Renderer* sdl_renderer) { renderer = sdl_renderer; }

    // TODO: Handle SDL_ errors. Supply a logger?

    void set_draw_color(float r, float g, float b, float a) {
        SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
    }

    void clear() { SDL_RenderClear(renderer); }

    void present() { SDL_RenderPresent(renderer); }

  private:
    SDL_Renderer* renderer {nullptr};
};

} // namespace engine
#endif
