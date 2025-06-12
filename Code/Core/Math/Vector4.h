#pragma once

#include "Core/Math/Vector3.h"
class [[nodiscard]] Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

    Vector4 &Add(const Vector4 &other);
    Vector4 &Subtract(const Vector4 &other);
    Vector4 &Multiply(const Vector4 &other);

    Vector4 Normalized() const;

    float Dot(const Vector4 &other) const;

    float GetLength() const;

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }
    float GetW() const { return w; }

    Vector3 GetXYZ() const;

    Vector4 &operator+=(const Vector4 &rhs);
    Vector4 &operator-=(const Vector4 &rhs);
    Vector4 &operator*=(const Vector4 &rhs);

    Vector4 operator+(const Vector4 &rhs) const;
    Vector4 operator-(const Vector4 &rhs) const;
    Vector4 operator*(const Vector4 &rhs) const;

    Vector4 operator-() const;
};
