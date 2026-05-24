#ifndef ENGINE_INIT_H
#define ENGINE_INIT_H

namespace engine {
class Init {
  public:
    SDL_Window* window {NULL};
    SDL_Renderer* renderer {NULL};

    Init(const char* window_title, int window_width, int window_heigth);
    ~Init() { SDL_Quit(); }
};
} // namespace engine

#endif
