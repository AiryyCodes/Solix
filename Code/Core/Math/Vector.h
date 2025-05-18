#pragma once

class Vector3
{
public:
    Vector3()
        : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {}

    Vector3 &Add(const Vector3 &other);
    Vector3 &Subtract(const Vector3 &other);
    Vector3 &Multiply(const Vector3 &other);

    Vector3 &operator+=(const Vector3 &rhs) { return Add(rhs); }
    Vector3 &operator-=(const Vector3 &rhs) { return Subtract(rhs); }
    Vector3 &operator*=(const Vector3 &rhs) { return Multiply(rhs); }

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }

public:
    float x;
    float y;
    float z;
};
