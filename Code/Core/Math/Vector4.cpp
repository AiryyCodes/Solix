#include "Core/Math/Vector4.h"
#include "Core/Math/Vector3.h"

#include <cmath>

Vector4 &Vector4::Add(const Vector4 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4 &Vector4::Subtract(const Vector4 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4 &Vector4::Multiply(const Vector4 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

Vector4 Vector4::Normalized() const
{
    float length = GetLength();
    if (length == 0.0f)
    {
        // Return a zeroed out vector
        return Vector4();
    }

    Vector4 result;
    result.x = x / length;
    result.y = y / length;
    result.z = z / length;
    result.w = w / length;

    return result;
}

float Vector4::Dot(const Vector4 &other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::GetLength() const
{
    return sqrt(Dot(*this));
}

Vector3 Vector4::GetXYZ() const
{
    return Vector3(x, y, z);
}

Vector4 &Vector4::operator+=(const Vector4 &rhs) { return Add(rhs); }
Vector4 &Vector4::operator-=(const Vector4 &rhs) { return Subtract(rhs); }
Vector4 &Vector4::operator*=(const Vector4 &rhs) { return Multiply(rhs); }

Vector4 Vector4::operator+(const Vector4 &rhs) const
{
    Vector4 result = *this;
    result += rhs;

    return result;
}

Vector4 Vector4::operator-(const Vector4 &rhs) const
{
    Vector4 result = *this;
    result -= rhs;

    return result;
}

Vector4 Vector4::operator*(const Vector4 &rhs) const
{
    Vector4 result = *this;
    result *= rhs;

    return result;
}

Vector4 Vector4::operator-() const
{
    Vector4 result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}
