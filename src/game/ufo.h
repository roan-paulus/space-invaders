#ifndef UFO_H
#define UFO_H

#include "game/animation.h"
#include "game/resource.h"
#include <random>
#include <chrono>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <engine/vec2.h>
#include <game/texture.h>
#include <game/projectile.h>
#include <game/collision.h>
#include <vector>

struct UFO {
    static constexpr float width{ 64 };
    static constexpr float points{ 10 };

    int hitpoints;
    SDL_FRect body;
    Vec2 velocity;
    Texture* texture;

    UFO(int hitpoints, Texture* texture, SDL_FRect* game_frame)
    : hitpoints{ hitpoints }
    , velocity{ -50, 0 }
    , body{
        .x = game_frame->w - width,
        .y = 5,
        .w = width,
        .h = 64,
    }
    , texture{ texture }
    {}

    void update(float delta_time, Projectile* projectile) {
        body.x += velocity.x * delta_time;

        if (projectile != nullptr && has_collision(body, projectile->body)) {
            projectile->out_of_bounds = true;
            --hitpoints;
        }
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderTexture(renderer, texture->texture, &texture->frame, &body);
    }
};

class UFOS {
public:
    std::vector<UFO> ufos;

    void push(UFO ufo) {
        ufos.push_back(ufo);
    }

    void update(float delta_time, Projectile* projectile) {
        for (auto& ufo : ufos) {
            ufo.update(delta_time, projectile);
        }
    }

    void draw(SDL_Renderer* renderer) {
        for (auto& ufo : ufos) {
            ufo.draw(renderer);
        }
    }
};

class UFOSpawner {
    std::mt19937 random_number_generator;
    Texture* texture;
    SDL_FRect* game_frame;

public:
    UFOS ufos;

    UFOSpawner(Texture* texture, SDL_FRect* game_frame)
    : random_number_generator{
        static_cast<std::mt19937::result_type>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        )
    }
    , texture{ texture }
    , game_frame{ game_frame }
    {}

    bool should_spawn() {
        if (ufos.ufos.size() > 0) {
            return false;
        }
        std::uniform_int_distribution generate_random_number{ 1, 1000 };
        int i = generate_random_number(this->random_number_generator);
        return i > 999;
    }

    void spawn() {
        const int hitpoints = 1;
        UFO ufo = { hitpoints, texture, game_frame };
        ufos.push(ufo);
    }

    void despawn(std::vector<AnimationObject>& animation_queue, Resources& resources) {
        UFO ufo = ufos.ufos.back();
        animation_queue.push_back(
            {
                .animation = resources.explosion,
                .location = {
                // Subtraction to get to optimal animation position.
                ufo.body.x - 8,
                ufo.body.y - 16,
                64,
                64,
                }
            }
        );
        ufos.ufos.pop_back();
    }
};

#endif
