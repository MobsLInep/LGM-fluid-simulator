#pragma once
#include <cmath>

namespace lbm {

struct Vector2D {
    double x;
    double y;

    constexpr Vector2D() : x(0.0), y(0.0) {}
    constexpr Vector2D(double x_, double y_) : x(x_), y(y_) {}

    Vector2D operator+(const Vector2D& rhs) const { return {x + rhs.x, y + rhs.y}; }
    Vector2D operator-(const Vector2D& rhs) const { return {x - rhs.x, y - rhs.y}; }
    Vector2D operator*(double s) const { return {x * s, y * s}; }
    Vector2D operator/(double s) const { return {x / s, y / s}; }
    Vector2D& operator+=(const Vector2D& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vector2D& operator-=(const Vector2D& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vector2D& operator*=(double s) { x *= s; y *= s; return *this; }
    Vector2D& operator/=(double s) { x /= s; y /= s; return *this; }

    double dot(const Vector2D& rhs) const { return x * rhs.x + y * rhs.y; }
    double magnitude() const { return std::sqrt(x * x + y * y); }
    Vector2D normalize() const {
        double m = magnitude();
        return m > 0.0 ? (*this) / m : Vector2D{};
    }
};

inline Vector2D operator*(double s, const Vector2D& v) { return v * s; }

}
