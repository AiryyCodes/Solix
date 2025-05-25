#pragma once

#include <cmath>
#include <cstddef>

template <typename Derived, size_t N>
class Vector
{
public:
    Vector()
    {
        for (int i = 0; i < N; i++)
        {
            m_Data[i] = 0.0f;
        }
    }

    template <typename... Args>
    Vector(Args... args) : m_Data{static_cast<float>(args)...}
    {
        static_assert(sizeof...(args) == N, "Wrong number of arguments");
    }

    Derived &Add(const Derived &other)
    {
        for (int i = 0; i < N; i++)
        {
            m_Data[i] += other.m_Data[i];
        }

        return static_cast<Derived &>(*this);
    }

    Derived &Subtract(const Derived &other)
    {
        for (int i = 0; i < N; i++)
        {
            m_Data[i] -= other.m_Data[i];
        }

        return static_cast<Derived &>(*this);
    }

    Derived &Multiply(const Derived &other)
    {
        for (int i = 0; i < N; i++)
        {
            m_Data[i] *= other.m_Data[i];
        }

        return static_cast<Derived &>(*this);
    }

    float Dot(const Derived &other) const
    {
        float result = 0.0f;
        for (int i = 0; i < N; i++)
        {
            result += m_Data[i] * other.m_Data[i];
        }

        return result;
    }

    float GetLength() const
    {
        return sqrt(Dot(static_cast<const Derived &>(*this)));
    }

    Derived Normalized() const
    {
        float length = GetLength();
        // TODO: Assert length != 0.0f

        Derived result;
        for (int i = 0; i < N; i++)
        {
            result.m_Data[i] = m_Data[i] / length;
        }

        return result;
    }

    Derived &operator+=(const Derived &rhs) { return Add(rhs); }
    Derived &operator-=(const Derived &rhs) { return Subtract(rhs); }
    Derived &operator*=(const Derived &rhs) { return Multiply(rhs); }

    Derived operator+(const Derived &rhs) const
    {
        Derived result = static_cast<const Derived &>(*this);
        result += rhs;

        return result;
    }

    Derived operator-(const Derived &rhs) const
    {
        Derived result = static_cast<const Derived &>(*this);
        result -= rhs;

        return result;
    }

    Derived operator*(const Derived &rhs) const
    {
        Derived result = static_cast<const Derived &>(*this);
        result *= rhs;

        return result;
    }

    Derived operator-() const
    {
        Derived result;
        for (int i = 0; i < N; i++)
        {
            result.m_Data[i] = -m_Data[i];
        }

        return result;
    }

protected:
    float m_Data[N];
};

class Vector2 : public Vector<Vector2, 2>
{
public:
    using Vector::Vector;

    float Cross(const Vector2 &other) const
    {
        return m_Data[0] * other.m_Data[1] - m_Data[1] * other.m_Data[0];
    }

    float &x() { return m_Data[0]; }
    float &y() { return m_Data[1]; }
    float x() const { return m_Data[0]; }
    float y() const { return m_Data[1]; }

    float GetX() const { return m_Data[0]; }
    float GetY() const { return m_Data[1]; }
};

class Vector3 : public Vector<Vector3, 3>
{
public:
    using Vector::Vector;

    Vector3 Cross(const Vector3 &other) const
    {
        return Vector3(
            m_Data[1] * other.m_Data[2] - m_Data[2] * other.m_Data[1],
            m_Data[2] * other.m_Data[0] - m_Data[0] * other.m_Data[2],
            m_Data[0] * other.m_Data[1] - m_Data[1] * other.m_Data[0]);
    }

    float &x() { return m_Data[0]; }
    float &y() { return m_Data[1]; }
    float &z() { return m_Data[2]; }
    float x() const { return m_Data[0]; }
    float y() const { return m_Data[1]; }
    float z() const { return m_Data[2]; }

    float GetX() const { return m_Data[0]; }
    float GetY() const { return m_Data[1]; }
    float GetZ() const { return m_Data[2]; }
};

class Vector4 : public Vector<Vector4, 4>
{
public:
    using Vector::Vector;

    float &x() { return m_Data[0]; }
    float &y() { return m_Data[1]; }
    float &z() { return m_Data[2]; }
    float &w() { return m_Data[3]; }
    float x() const { return m_Data[0]; }
    float y() const { return m_Data[1]; }
    float z() const { return m_Data[2]; }
    float w() const { return m_Data[3]; }

    float GetX() const { return m_Data[0]; }
    float GetY() const { return m_Data[1]; }
    float GetZ() const { return m_Data[2]; }
    float GetW() const { return m_Data[3]; }
};
