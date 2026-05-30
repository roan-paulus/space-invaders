#include "ship.h"

Ship create_ship() {
    Ship s = {
        .shape = {
            .x = start_pos_x,
            .y = start_pos_y,
            .w = width,
            .h = width,
        }
    };
    return s;
}
