#include "Core/Variant.h"
#include "Core/Math/Vector2.h"

#include <cstdint>
#include <new>

Variant::Variant()
{
    m_Type = Null;
}

Variant::~Variant()
{
    if (m_Type == Vector2)
        reinterpret_cast<class Vector2 *>(&m_Data.m_Vector2)->~Vector2();
}

Variant::Variant(int32_t value)
{
    m_Type = Int;
    m_Data.m_Int = value;
}

Variant::Variant(float value)
{
    m_Type = Float;
    m_Data.m_Float = value;
}

Variant::Variant(double value)
{
    m_Type = Float;
    m_Data.m_Float = value;
}

Variant::Variant(const class Vector2 &value)
{
    m_Type = Vector2;
    new (&m_Data.m_Vector2) class Vector2(value);
}

Variant::operator int32_t() const
{
    return ToInt<int32_t>();
}

Variant::operator float() const
{
    return ToFloat<float>();
}

Variant::operator double() const
{
    return ToFloat<double>();
}

Variant::operator class Vector2() const
{
    return *reinterpret_cast<const class Vector2 *>(&m_Data.m_Vector2);
}
