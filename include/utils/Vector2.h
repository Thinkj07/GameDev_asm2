#pragma once
#include <cmath>

struct Vector2 {
    float x, y;

    // === Constructors ===
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    // === Arithmetic Operators ===
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator*(float s) const {
        return Vector2(x * s, y * s);
    }

    Vector2 operator/(float s) const {
        return Vector2(x / s, y / s);
    }

    // Unary negation: -vec
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    // === Compound Assignment Operators ===
    Vector2& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2& operator*=(float s) {
        x *= s;
        y *= s;
        return *this;
    }

    Vector2& operator/=(float s) {
        x /= s;
        y /= s;
        return *this;
    }

    // === Comparison Operators ===
    bool operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector2& v) const {
        return !(*this == v);
    }

    // === Utility Methods ===

    // Tinh do dai vector
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Do dai binh phuong (tranh sqrt khi chi can so sanh)
    float lengthSquared() const {
        return x * x + y * y;
    }

    // Tich vo huong (dot product)
    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    // Khoang cach den vector khac
    float distance(const Vector2& v) const {
        return (*this - v).length();
    }

    // Chuan hoa vector (tra ve ban sao, khong thay doi ban goc)
    Vector2 normalize() const {
        float len = length();
        if (len > 0) {
            return Vector2(x / len, y / len);
        }
        return *this;
    }

    // Xoay vector theo goc (don vi: do / degrees)
    Vector2 rotate(float angleDeg) const {
        float rad = angleDeg * 3.14159265f / 180.0f;
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        return Vector2(x * cosA - y * sinA, x * sinA + y * cosA);
    }

    // Tao vector tu goc (degrees) voi do lon cho truoc
    static Vector2 fromAngle(float angleDeg, float magnitude = 1.0f) {
        float rad = angleDeg * 3.14159265f / 180.0f;
        return Vector2(std::cos(rad) * magnitude, std::sin(rad) * magnitude);
    }
};

// Cho phep: float * Vector2  (vi du: 2.0f * vec)
inline Vector2 operator*(float s, const Vector2& v) {
    return Vector2(v.x * s, v.y * s);
}