#include "../../include/entities/Explosion.h"

Explosion::Explosion(float x, float y, float maxR, float life)
    : position(x, y), 
      radius(0.0f),
      maxRadius(maxR), 
      lifetime(life), 
      elapsed(0.0f),
      active(true),
      r(255), g(200), b(50)
{
}

SDL_FRect Explosion::getRect() const {
    return { 
        position.x - radius, 
        position.y - radius, 
        radius * 2, 
        radius * 2 
    };
}

// update explosion

void Explosion::update(float deltaTime) {
    if (!active) return;

    elapsed += deltaTime;
    float progress = getProgress();

    if (progress >= 1.0f) {
        active = false;
        radius = maxRadius;
        return;
    }

    // radius decrease over time
    radius = maxRadius * progress;

    if (progress < 0.5f) {
        r = 255;
        g = (Uint8)(200 - progress * 200);
        b = (Uint8)(50 - progress * 100);
    } else {
        r = (Uint8)(255 - (progress - 0.5f) * 300);
        g = (Uint8)(100 - (progress - 0.5f) * 200);
        b = 0;
        if (r < 80) r = 80;
        if (g < 0) g = 0;
    }
}

bool Explosion::isFinished() const {
    return !active;
}

float Explosion::getProgress() const {
    if (lifetime <= 0.0f) return 1.0f;
    float p = elapsed / lifetime;
    return (p > 1.0f) ? 1.0f : p;
}
