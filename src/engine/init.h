#ifndef ENGINE_INIT_H
#define ENGINE_INIT_H

#include "event.h"
#include "renderer/renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

namespace engine {
class Init {
  public:
    Event event {};
    Renderer renderer {NULL};

    Init(const char* window_title, int window_width, int window_heigth);
    ~Init() { SDL_Quit(); }

  private:
    SDL_Window* window {NULL};
    SDL_Renderer* _renderer {NULL};
};
} // namespace engine

#endif
