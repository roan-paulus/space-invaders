#include "event.h"
#include "window_constants.h"
#include <renderer/rect.h>
#include <renderer/renderer.h>
#include <vector>

// Player start variables.
constexpr float width       = 30;
constexpr float start_pos_x = WINDOW_WIDTH / 2 - width / 2;
constexpr float start_pos_y = WINDOW_HEIGHT / 8 * 7;

struct Ship {
    Rect shape {};

    void handle_input(Event* event) {}
    // void update {}
    void draw(engine::Renderer* renderer) {
        renderer->set_draw_color(255, 255, 255, 255);
        renderer->draw_rect(&shape);
    }
};

struct Enemy {
    int x {0};
    int y {0};
    int width {0};
    int height {0};
};

namespace game {
struct World {
    Ship player {
        .shape = {
            .x = start_pos_x, .y = start_pos_y, .width = width, .height = 10
        }
    };
    std::vector<Enemy> enemies {};
};
} // namespace game
