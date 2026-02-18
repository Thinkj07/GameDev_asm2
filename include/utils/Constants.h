#pragma once

// === Screen ===
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// === Player Physics ===
const float GRAVITY = 2000.0f;
const float JUMP_FORCE = -900.0f;
const float MOVE_SPEED = 400.0f;

// === Player Stats ===
const float PLAYER_MAX_HP = 100.0f;
const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 40.0f;

// === Projectile / Bullet ===
const int MAX_BOUNCES = 5;
const float BULLET_SPEED = 800.0f;
const int MAX_PROJECTILES = 20;

// Sat thuong dan: ti le theo kich thuoc (charge nho -> min, charge max -> max)
const float MIN_BULLET_DAMAGE = 8.0f;
const float MAX_BULLET_DAMAGE = 30.0f;

// Sat thuong theo loai dan (Normal / Heavy / Sonic) - cho he thong reload sau nay
const float DAMAGE_NORMAL = 15.0f;
const float DAMAGE_HEAVY = 30.0f;
const float DAMAGE_SONIC = 8.0f;

// Toc do dan theo loai
const float SPEED_NORMAL = 800.0f;
const float SPEED_HEAVY = 500.0f;
const float SPEED_SONIC = 1200.0f;

// Trong luc tac dong len dan (Heavy chiu nhieu hon)
const float BULLET_GRAVITY_NORMAL = 0.0f;
const float BULLET_GRAVITY_HEAVY = 600.0f;
const float BULLET_GRAVITY_SONIC = 0.0f;

// === Charge System ===
const float MAX_CHARGE_TIME = 1.0f;
const float MIN_BULLET_RADIUS = 8.0f;
const float MAX_BULLET_RADIUS = 25.0f;

// === Mana System ===
const float MAX_MANA = 100.0f;
const float MANA_REGEN = 15.0f;
const float MANA_COST = 20.0f;

// === Aiming ===
const float ROT_TIME = 2.0f;
const float AIM_LENGTH = 60.0f;
const float PI = 3.14159265f;

// === Wind System (spec: doi chieu moi 10 giay) ===
const float WIND_CHANGE_INTERVAL = 10.0f;
const float WIND_FORCE_MIN = -150.0f;
const float WIND_FORCE_MAX = 150.0f;

// === Effect Zones ===
const float ZONE_SPEED_MULTIPLIER = 2.0f;
const float ZONE_SLOW_MULTIPLIER = 0.5f;

// === Explosion ===
const float EXPLOSION_LIFETIME = 0.4f;
const float EXPLOSION_MAX_RADIUS = 30.0f;