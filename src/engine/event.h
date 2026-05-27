#ifndef EVENT_H
#define EVENT_H

struct Event {
    bool keep_playing {true};

    bool poll() { return SDL_PollEvent(&event); }
    void handle() {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
            keep_playing = false;
        }
        case SDL_EVENT_KEY_DOWN: {
            if (event.key.scancode == SDL_SCANCODE_Q) {
                keep_playing = false;
            }
        }
        }
    }

  private:
    SDL_Event event {};
};

#endif
