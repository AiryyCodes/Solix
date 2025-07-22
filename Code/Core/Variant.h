#pragma once

#include "Core/Math/Vector2.h"
#include <cstdint>
#include <type_traits>

class Variant
{
public:
    enum Type
    {
        Null,
        Int,
        Float,

        Vector2,
    };

public:
    Type GetType() const { return m_Type; }

private:
    Type m_Type = Null;

    union
    {
        int64_t m_Int;
        double m_Float;

        std::aligned_storage_t<sizeof(Vector2), alignof(Vector2)> m_Vector2;
    } m_Data;

    template <typename T>
    T ToInt() const
    {
        switch (m_Type)
        {
        case Null:
            return 0;
        case Int:
            return T(m_Data.m_Int);
        case Float:
            return T(m_Data.m_Float);
        default:
            return 0;
        }
    }

    template <typename T>
    T ToFloat() const
    {
        switch (m_Type)
        {
        case Null:
            return 0.0f;
        case Int:
            return T(m_Data.m_Int);
        case Float:
            return T(m_Data.m_Float);
        default:
            return 0.0f;
        }
    }

public:
    Variant();
    ~Variant();

    Variant(int32_t value);
    Variant(float value);
    Variant(double value);
    Variant(const class Vector2 &value);

    operator int32_t() const;
    operator float() const;
    operator double() const;
    operator class Vector2() const;
};
