#pragma once
#include <SDL3/SDL.h>
#include "../utils/Vector2.h"

struct Projectile {
    Vector2 position;
    Vector2 velocity;
    float radius;
    int ownerId;
    bool active;
    int bounceCount;
    float existTime; 
    float damage;

    Projectile(float x, float y, float velX, float velY, float r, int owner);
    SDL_FRect getRect() const;

    void update(float deltaTime);
    bool checkWallBounce();
    bool checkPlatformBounce(const SDL_FRect& platRect);
    bool checkHitPlayer(const SDL_FRect& playerRect);

    void deactivate();
};
