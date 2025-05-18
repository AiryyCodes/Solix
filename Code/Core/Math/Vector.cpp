#include "Core/Math/Vector.h"

Vector3 &Vector3::Add(const Vector3 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

Vector3 &Vector3::Subtract(const Vector3 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

Vector3 &Vector3::Multiply(const Vector3 &other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;

    return *this;
}
