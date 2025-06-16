#include "Core/Math/Vector3.h"

#include <cmath>

Vector3 &Vector3::Add(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3 &Vector3::Subtract(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3 &Vector3::Multiply(const Vector3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Vector3 &Vector3::Multiply(float other)
{
    x *= other;
    y *= other;
    z *= other;

    return *this;
}

Vector3 Vector3::Normalized() const
{
    float length = GetLength();
    if (length == 0.0f)
    {
        // Return a zeroed out vector
        return Vector3();
    }

    Vector3 result;
    result.x = x / length;
    result.y = y / length;
    result.z = z / length;

    return result;
}

Vector3 Vector3::Cross(const Vector3 &other) const
{
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

float Vector3::Dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vector3::Vector3::GetLength() const
{
    return sqrt(Dot(*this));
}

Vector3 &Vector3::operator+=(const Vector3 &rhs) { return Add(rhs); }
Vector3 &Vector3::operator-=(const Vector3 &rhs) { return Subtract(rhs); }
Vector3 &Vector3::operator*=(const Vector3 &rhs) { return Multiply(rhs); }
Vector3 &Vector3::operator*=(float rhs) { return Multiply(rhs); }

Vector3 Vector3::operator+(const Vector3 &rhs) const
{
    Vector3 result = *this;
    result += rhs;

    return result;
}

Vector3 Vector3::operator-(const Vector3 &rhs) const
{
    Vector3 result = *this;
    result -= rhs;

    return result;
}

Vector3 Vector3::operator*(const Vector3 &rhs) const
{
    Vector3 result = *this;
    result *= rhs;

    return result;
}

Vector3 Vector3::operator*(float rhs) const
{
    Vector3 result = *this;
    result *= rhs;

    return result;
}

Vector3 Vector3::operator-() const
{
    Vector3 result;
    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}
