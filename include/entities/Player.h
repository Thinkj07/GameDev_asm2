#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "../utils/Vector2.h"
#include "../utils/Constants.h"

struct Projectile;
struct Platform;

struct Player {
    int id;
    Vector2 position;
    Vector2 velocity;
    float width, height;
    bool isGrounded;
    float hp;
    float maxHp;
    float mana;
    float maxMana;
    float shootCooldown;
    float currentChargeTime; 
    bool isCharging;

    float aimAngle;
    Uint8 r, g, b;

    // === Constructor & Getter ===
    Player(int playerId, float x, float y); 
    SDL_FRect getRect() const;

    // === Di chuyen (spec: Move, Jump) ===
    void move(float direction);
    void jump();
    void applyGravity(float deltaTime);
    void updatePosition(float deltaTime);

    // === Chien dau (spec: Shoot, Reload) ===
    void startCharge(float deltaTime);
    void releaseShoot(std::vector<Projectile>& bullets);
    void takeDamage(float amount);
    bool isAlive() const;

    // === Cap nhat he thong ===
    void updateAim(float deltaTime);
    void regenMana(float deltaTime);
    void updateCooldown(float deltaTime);

    // === Va cham ===
    void clampToScreen();
    void checkPlatformCollision(const std::vector<Platform>& platforms);
};
