#pragma once
#include <SDL3/SDL.h>
#include "../utils/Vector2.h"

struct Explosion {
    Vector2 position;
    float radius;
    float maxRadius;
    float lifetime;
    float elapsed;
    bool active;

    Uint8 r, g, b;

    // === Constructor & Getter ===
    Explosion(float x, float y, float maxR, float life);
    SDL_FRect getRect() const;

    // === Cap nhat ===
    void update(float deltaTime);
    bool isFinished() const;
    float getProgress() const;
};
