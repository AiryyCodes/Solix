#include "Core/Math/Vector2.h"

#include <cmath>

Vector2 &Vector2::Add(const Vector2 &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2 &Vector2::Subtract(const Vector2 &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2 &Vector2::Multiply(const Vector2 &other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

Vector2 Vector2::Normalized() const
{
    float length = GetLength();
    if (length == 0.0f)
    {
        // Return a zeroed out vector
        return Vector2();
    }

    Vector2 result;
    result.x = x / length;
    result.y = y / length;

    return result;
}

float Vector2::Cross(const Vector2 &other) const
{
    return x * other.y - y * other.x;
}

float Vector2::Dot(const Vector2 &other) const
{
    return x * other.x + y * other.y;
}

float Vector2::GetLength() const
{
    return sqrt(Dot(*this));
}

Vector2 &Vector2::operator+=(const Vector2 &rhs) { return Add(rhs); }
Vector2 &Vector2::operator-=(const Vector2 &rhs) { return Subtract(rhs); }
Vector2 &Vector2::operator*=(const Vector2 &rhs) { return Multiply(rhs); }

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
    Vector2 result = *this;
    result += rhs;

    return result;
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
    Vector2 result = *this;
    result -= rhs;

    return result;
}

Vector2 Vector2::operator*(const Vector2 &rhs) const
{
    Vector2 result = *this;
    result *= rhs;

    return result;
}

Vector2 Vector2::operator-() const
{
    Vector2 result;
    result.x = -x;
    result.y = -y;

    return result;
}
