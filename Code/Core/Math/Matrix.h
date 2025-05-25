#pragma once

#include "Core/Math/Vector.h"

class Matrix4
{
public:
    void Translate(const Vector2 &translation);

    void Scale(const Vector2 &scale);
    void Scale(const Vector3 &scale);

    void RotateX(float rotation);
    void RotateY(float rotation);
    void RotateZ(float rotation);

    float *GetValue() const;

    static Matrix4 Identity();
    static Matrix4 Orthographic(float left, float right, float top, float bottom, float far = -1.0f, float near = 1.0f);
    static Matrix4 LookAt(Vector2 eye, Vector2 target);

    Matrix4 operator*(const Matrix4 &other) const;

public:
    Vector4 m_Column[4];

    mutable float m_Values[16];
};
