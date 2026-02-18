#include "../../include/entities/Player.h"
#include "../../include/entities/Projectile.h"
#include "../../include/entities/Platform.h"
#include "../../include/utils/Constants.h"
#include <cmath>

Player::Player(int playerId, float startX, float startY) 
    : id(playerId), 
      position(startX, startY), 
      velocity(0, 0), 
      width(PLAYER_WIDTH), height(PLAYER_HEIGHT),
      isGrounded(false),
      hp(PLAYER_MAX_HP), maxHp(PLAYER_MAX_HP),
      mana(MAX_MANA), maxMana(MAX_MANA), 
      shootCooldown(0),
      currentChargeTime(0.0f), isCharging(false),
      aimAngle(0.0f),
      r(0), g(0), b(0)
{
    if (id == 1) { 
        r = 255; g = 50; b = 50; 
        aimAngle = 0.0f;
    }    
    else { 
        r = 50; g = 50; b = 255; 
        aimAngle = 180.0f;
    }  
}

SDL_FRect Player::getRect() const { 
    return { position.x, position.y, width, height }; 
}

// move player

void Player::move(float direction) {
    velocity.x = direction * MOVE_SPEED;
}

void Player::jump() {
    if (isGrounded) {
        velocity.y = JUMP_FORCE;
        isGrounded = false;
    }
}

void Player::applyGravity(float deltaTime) {
    velocity.y += GRAVITY * deltaTime;
}

void Player::updatePosition(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

// charge and shoot

void Player::startCharge(float deltaTime) {
    if (mana >= MANA_COST) {
        isCharging = true;
        currentChargeTime += deltaTime;
        if (currentChargeTime > MAX_CHARGE_TIME) {
            currentChargeTime = MAX_CHARGE_TIME;
        }
    }
}

void Player::releaseShoot(std::vector<Projectile>& bullets) {
    if (currentChargeTime <= 0.0f) {
        isCharging = false;
        return;
    }

    if (mana < MANA_COST || shootCooldown > 0.0f) {
        currentChargeTime = 0.0f;
        isCharging = false;
        return;
    }

    float ratio = currentChargeTime / MAX_CHARGE_TIME;
    float bulletRadius = MIN_BULLET_RADIUS + (MAX_BULLET_RADIUS - MIN_BULLET_RADIUS) * ratio;

    float rad = aimAngle * (PI / 180.0f);
    float velX = std::cos(rad) * BULLET_SPEED;
    float velY = std::sin(rad) * BULLET_SPEED;

    float centerX = position.x + width / 2.0f;
    float centerY = position.y + height / 2.0f;
    float spawnX = centerX - bulletRadius;
    float spawnY = centerY - bulletRadius;

    int myBullets = 0;
    for (const auto& b : bullets) {
        if (b.ownerId == id && b.active) myBullets++;
    }

    if (myBullets < MAX_PROJECTILES) {
        bullets.push_back(Projectile(spawnX, spawnY, velX, velY, bulletRadius, id));
        mana -= MANA_COST;
        shootCooldown = 0.2f;
    }

    currentChargeTime = 0.0f;
    isCharging = false;
}

void Player::takeDamage(float amount) {
    hp -= amount;
    if (hp < 0.0f) hp = 0.0f;
}

bool Player::isAlive() const {
    return hp > 0.0f;
}

// update system

void Player::updateAim(float deltaTime) {
    float rotSpeed = 360.0f / ROT_TIME;
    aimAngle += rotSpeed * deltaTime;
    if (aimAngle >= 360.0f) aimAngle -= 360.0f;
}

void Player::regenMana(float deltaTime) {
    if (mana < maxMana) {
        mana += MANA_REGEN * deltaTime;
        if (mana > maxMana) mana = maxMana;
    }
}

void Player::updateCooldown(float deltaTime) {
    if (shootCooldown > 0.0f) {
        shootCooldown -= deltaTime;
    }
}

// collision

void Player::clampToScreen() {
    isGrounded = false;

    if (position.x < 0) position.x = 0;
    if (position.x > SCREEN_WIDTH - width) position.x = SCREEN_WIDTH - width;

    if (position.y > SCREEN_HEIGHT - height) {
        position.y = SCREEN_HEIGHT - height;
        velocity.y = 0;
        isGrounded = true;
    }
}

void Player::checkPlatformCollision(const std::vector<Platform>& platforms) {
    for (const auto& plat : platforms) {
        bool collisionX = (position.x + width > plat.x) && (position.x < plat.x + plat.width);
        bool falling = velocity.y >= 0;
        bool feetHitting = (position.y + height >= plat.y) && (position.y + height <= plat.y + 20);

        if (collisionX && falling && feetHitting) {
            position.y = plat.y - height;
            velocity.y = 0;
            isGrounded = true;
        }
    }
}
