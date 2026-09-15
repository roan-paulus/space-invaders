#ifndef GAME_TIMER_H
#define GAME_TIMER_H

struct GameTimer {
    float length;
    float time{ 0 };
    bool timeout{ false };

    void step(float delta_time) {
        time += delta_time;

        if (time >= length) {
            time -= length;
            timeout = true;
        }
    }

    bool is_timeout_and_step(float delta_time) {
        step(delta_time);
        if (timeout) {
            timeout = false;
            return true;
        }
        return false;
    }

    void reset() {
        time = 0;
    }
};

#endif
