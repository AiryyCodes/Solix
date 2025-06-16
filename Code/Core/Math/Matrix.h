#pragma once

#include "Core/Assert.h"
#include "Core/Math/Vector.h"

class Matrix4
{
public:
    Matrix4() = default;
    Matrix4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4)
    {
        m_Column[0] = col1;
        m_Column[1] = col2;
        m_Column[2] = col3;
        m_Column[3] = col4;
    }

    void Translate(const Vector2 &translation);
    void Translate(const Vector3 &translation);

    void Scale(const Vector2 &scale);
    void Scale(const Vector3 &scale);

    void RotateX(float rotation);
    void RotateY(float rotation);
    void RotateZ(float rotation);

    float *GetValue() const;

    static Matrix4 Identity();

    static Matrix4 Orthographic(float left, float right, float top, float bottom, float near = -1.0f, float far = 1.0f);
    static Matrix4 Perspective(float fov, float aspect, float near = 0.01f, float far = 100.0f);

    static Matrix4 LookAt(const Vector2 &eye, const Vector2 &target);
    static Matrix4 LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
    static Matrix4 LookAt(const Vector3 &position, const Vector3 &right, const Vector3 &up, const Vector3 &front);

    Matrix4 operator*(const Matrix4 &other) const;
    Matrix4 operator=(const Matrix4 &other);

    const Vector4 &operator[](int index) const
    {
        ASSERT(index >= 0 && index < 4, "Matrix column index out of bounds");
        return m_Column[index];
    }

    Vector4 &operator[](int index)
    {
        ASSERT(index >= 0 && index < 4, "Matrix column index out of bounds");
        return m_Column[index];
    }

public:
    Vector4 m_Column[4];

    mutable float m_Values[16];
};

class Matrix3
{
public:
    Matrix3() = default;
    Matrix3(Vector3 col1, Vector3 col2, Vector3 col3)
    {
        m_Column[0] = col1;
        m_Column[1] = col2;
        m_Column[2] = col3;
    }

    static Matrix3 RotationAxis(const Vector3 &axis, float angle);

    Vector3 operator*(const Vector3 &vector);

    const Vector3 &operator[](int index) const
    {
        ASSERT(index >= 0 && index < 3, "Matrix column index out of bounds");
        return m_Column[index];
    }

    Vector3 &operator[](int index)
    {
        ASSERT(index >= 0 && index < 3, "Matrix column index out of bounds");
        return m_Column[index];
    }

private:
    Vector3 m_Column[3];
};
