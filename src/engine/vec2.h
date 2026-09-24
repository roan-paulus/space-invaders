#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
    float x;
    float y;

    Vec2 operator+(Vec2 b) {
        return {
            .x = x + b.x,
            .y = y + b.y
        };
    }

    Vec2 operator-(Vec2 b) {
        return {
            .x = x - b.x,
            .y = y - b.y 
        };
    }

    Vec2 operator*(Vec2 b) {
        return {
            .x = x * b.x,
            .y = y * b.y
        };
    }
};

#endif
