#pragma once

class [[nodiscard]] Vector2
{
public:
    float x;
    float y;

    Vector2()
        : x(0.0f), y(0.0f) {}
    Vector2(float x, float y)
        : x(x), y(y) {}

    Vector2 &Add(const Vector2 &other);
    Vector2 &Subtract(const Vector2 &other);
    Vector2 &Multiply(const Vector2 &other);

    Vector2 Normalized() const;

    float Cross(const Vector2 &other) const;
    float Dot(const Vector2 &other) const;

    float GetLength() const;

    float GetX() const { return x; }
    float GetY() const { return y; }

    Vector2 &operator+=(const Vector2 &rhs);
    Vector2 &operator-=(const Vector2 &rhs);
    Vector2 &operator*=(const Vector2 &rhs);

    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 operator-(const Vector2 &rhs) const;
    Vector2 operator*(const Vector2 &rhs) const;

    Vector2 operator-() const;
};
