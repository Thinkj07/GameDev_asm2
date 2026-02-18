#include "../../include/entities/Projectile.h"
#include "../../include/utils/Constants.h"

Projectile::Projectile(float x, float y, float velX, float velY, float r, int owner, float damage)
    : position(x, y), 
      velocity(velX, velY), 
      radius(r), 
      ownerId(owner), 
      active(true), 
      bounceCount(0),
      existTime(0.0f),
      damage(damage)
{
    float range = MAX_BULLET_RADIUS - MIN_BULLET_RADIUS;
    float ratio = (range > 0.0f) ? (radius - MIN_BULLET_RADIUS) / range : 0.0f;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;
    damage = MIN_BULLET_DAMAGE + (MAX_BULLET_DAMAGE - MIN_BULLET_DAMAGE) * ratio;
}

SDL_FRect Projectile::getRect() const { 
    return { position.x, position.y, radius * 2, radius * 2 }; 
}

// update position

void Projectile::update(float deltaTime) {
    if (!active) return;
    existTime += deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

// wall bounce

bool Projectile::checkWallBounce() {
    if (!active || existTime < 0.05f) return false;

    bool bounced = false;

    // left and right wall
    if (position.x <= 0) { 
        position.x = 0; 
        velocity.x = -velocity.x; 
        bounced = true; 
    }
    else if (position.x >= SCREEN_WIDTH - radius * 2) { 
        position.x = SCREEN_WIDTH - radius * 2; 
        velocity.x = -velocity.x; 
        bounced = true; 
    }
    
// top and bottom wall
    if (position.y <= 0) { 
        position.y = 0; 
        velocity.y = -velocity.y; 
        bounced = true; 
    }
    else if (position.y >= SCREEN_HEIGHT - radius * 2) { 
        position.y = SCREEN_HEIGHT - radius * 2; 
        velocity.y = -velocity.y; 
        bounced = true; 
    }

    if (bounced) {
        bounceCount++;
        if (bounceCount >= MAX_BOUNCES) active = false;
    }

    return bounced;
}

// platform bounce

bool Projectile::checkPlatformBounce(const SDL_FRect& platRect) {
    if (!active) return false;

    SDL_FRect bulletRect = getRect();
    SDL_FRect intersection;

    if (SDL_GetRectIntersectionFloat(&bulletRect, &platRect, &intersection)) {
        // bounce based on the smaller intersection
        if (intersection.w < intersection.h) {
            velocity.x = -velocity.x;
            if (position.x < platRect.x) 
                position.x -= intersection.w;
            else 
                position.x += intersection.w;
        } 
        else {
            velocity.y = -velocity.y;
            if (position.y < platRect.y) 
                position.y -= intersection.h;
            else 
                position.y += intersection.h;
        }

        bounceCount++;
        if (bounceCount >= MAX_BOUNCES) {
            active = false;
        }
        return true;
    }

    return false;
}

// player collision

bool Projectile::checkHitPlayer(const SDL_FRect& playerRect) {
    if (!active || existTime < 0.05f) return false;

    SDL_FRect bulletRect = getRect();

    bool hit = (bulletRect.x < playerRect.x + playerRect.w) &&
               (bulletRect.x + bulletRect.w > playerRect.x) &&
               (bulletRect.y < playerRect.y + playerRect.h) &&
               (bulletRect.y + bulletRect.h > playerRect.y);

    if (hit) {
        active = false;
        return true;
    }

    return false;
}

// deactivate projectile

void Projectile::deactivate() {
    active = false;
}
