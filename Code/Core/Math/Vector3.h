#pragma once

class [[nodiscard]] Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3()
        : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {}

    Vector3 &Add(const Vector3 &other);
    Vector3 &Subtract(const Vector3 &other);
    Vector3 &Multiply(const Vector3 &other);
    Vector3 &Multiply(float other);

    Vector3 Normalized() const;
    Vector3 Cross(const Vector3 &other) const;

    float Dot(const Vector3 &other) const;

    float GetLength() const;

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }

    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);
    Vector3 &operator*=(const Vector3 &rhs);
    Vector3 &operator*=(float rhs);

    Vector3 operator+(const Vector3 &rhs) const;
    Vector3 operator-(const Vector3 &rhs) const;
    Vector3 operator*(const Vector3 &rhs) const;
    Vector3 operator*(float rhs) const;

    Vector3 operator-() const;
};
