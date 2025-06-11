#include "Core/Math/Matrix.h"
#include "Core/Math/Vector.h"

#include <cmath>

void Matrix4::Translate(const Vector2 &translation)
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.m_Column[3].x = translation.x;
    matrix.m_Column[3].y = translation.y;

    *this = (*this) * matrix;
}

void Matrix4::Translate(const Vector3 &translation)
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.m_Column[3].x = translation.x;
    matrix.m_Column[3].y = translation.y;
    matrix.m_Column[3].z = translation.z;

    *this = (*this) * matrix;
}

void Matrix4::Scale(const Vector2 &scale)
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.m_Column[0].x = scale.x;
    matrix.m_Column[1].y = scale.y;

    *this = (*this) * matrix;
}

void Matrix4::Scale(const Vector3 &scale)
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.m_Column[0].x = scale.x;
    matrix.m_Column[1].y = scale.y;
    matrix.m_Column[2].z = scale.z;

    *this = (*this) * matrix;
}

void Matrix4::RotateX(float rotation)
{
    Matrix4 rot = Matrix4::Identity();

    rot.m_Column[1].x = cos(rotation);
    rot.m_Column[1].y = sin(rotation);

    rot.m_Column[2].x = -sin(rotation);
    rot.m_Column[2].y = cos(rotation);

    *this = (*this) * rot;
}

void Matrix4::RotateY(float rotation)
{
    Matrix4 rot = Matrix4::Identity();

    rot.m_Column[0].x = cos(rotation);
    rot.m_Column[0].z = -sin(rotation);

    rot.m_Column[2].x = sin(rotation);
    rot.m_Column[2].z = cos(rotation);

    *this = (*this) * rot;
}

void Matrix4::RotateZ(float rotation)
{
    Matrix4 rot = Matrix4::Identity();

    rot.m_Column[0].x = cos(rotation);
    rot.m_Column[0].y = sin(rotation);

    rot.m_Column[1].x = -sin(rotation);
    rot.m_Column[1].y = cos(rotation);

    *this = (*this) * rot;
}

float *Matrix4::GetValue() const
{
    m_Values[0] = m_Column[0].x;
    m_Values[1] = m_Column[0].y;
    m_Values[2] = m_Column[0].z;
    m_Values[3] = m_Column[0].w;

    m_Values[4] = m_Column[1].x;
    m_Values[5] = m_Column[1].y;
    m_Values[6] = m_Column[1].z;
    m_Values[7] = m_Column[1].w;

    m_Values[8] = m_Column[2].x;
    m_Values[9] = m_Column[2].y;
    m_Values[10] = m_Column[2].z;
    m_Values[11] = m_Column[2].w;

    m_Values[12] = m_Column[3].x;
    m_Values[13] = m_Column[3].y;
    m_Values[14] = m_Column[3].z;
    m_Values[15] = m_Column[3].w;

    return m_Values;
}

Matrix4 Matrix4::Identity()
{
    Matrix4 matrix;
    matrix.m_Column[0].x = 1.0f;
    matrix.m_Column[1].y = 1.0f;
    matrix.m_Column[2].z = 1.0f;
    matrix.m_Column[3].w = 1.0f;

    return matrix;
}

Matrix4 Matrix4::Orthographic(float left, float right, float top, float bottom, float near, float far)
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.m_Column[0].x = 2 / (right - left);
    matrix.m_Column[1].y = 2 / (top - bottom);
    matrix.m_Column[2].z = -2 / (far - near);

    matrix.m_Column[3].x = -(right + left) / (right - left);
    matrix.m_Column[3].y = -(top + bottom) / (top - bottom);
    matrix.m_Column[3].z = -(far + near) / (far - near);

    return matrix;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far)
{
    float f = 1.0f / tan(fov / 2.0f);

    Matrix4 matrix = {}; // Zero initialize

    matrix.m_Column[0].x = f / aspect;
    matrix.m_Column[1].y = f;
    matrix.m_Column[2].z = (far + near) / (near - far);
    matrix.m_Column[2].w = -1.0f;
    matrix.m_Column[3].z = (2.0f * far * near) / (near - far);

    return matrix;
}

Matrix4 Matrix4::LookAt(const Vector2 &eye, const Vector2 &target)
{
    Vector2 forward = (target - eye).Normalized();
    Vector2 right = Vector2(-forward.y, forward.x);

    Matrix4 matrix;
    matrix.m_Column[0].x = right.x;
    matrix.m_Column[0].y = right.y;
    matrix.m_Column[0].z = 0.0f;
    matrix.m_Column[0].w = 0.0f;

    matrix.m_Column[1].x = 0.0f;
    matrix.m_Column[1].y = 0.0f;
    matrix.m_Column[1].z = 1.0f;
    matrix.m_Column[1].w = 0.0f;

    matrix.m_Column[2].x = -forward.x;
    matrix.m_Column[2].y = -forward.y;
    matrix.m_Column[2].z = 0.0f;
    matrix.m_Column[2].w = 0.0f;

    matrix.m_Column[3].x = -right.Dot(eye);
    matrix.m_Column[3].y = -Vector2(0.0f, 0.0f).Dot(eye);
    matrix.m_Column[3].z = forward.Dot(eye);
    matrix.m_Column[3].w = 1.0f;

    return matrix;
}

Matrix4 Matrix4::LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
{
    Vector3 f = (target - eye).Normalized(); // Forward
    Vector3 r = f.Cross(up).Normalized();    // Right
    Vector3 u = r.Cross(f);                  // Up (orthogonalized)

    Matrix4 matrix;

    // Orientation
    matrix.m_Column[0] = Vector4(r.x, u.x, -f.x, 0.0f);
    matrix.m_Column[1] = Vector4(r.y, u.y, -f.y, 0.0f);
    matrix.m_Column[2] = Vector4(r.z, u.z, -f.z, 0.0f);

    // Translation
    matrix.m_Column[3] = Vector4(
        -r.Dot(eye),
        -u.Dot(eye),
        f.Dot(eye),
        1.0f);

    return matrix;
}

Matrix4 Matrix4::LookAt(const Vector3 &position, const Vector3 &right, const Vector3 &up, const Vector3 &front)
{
    Matrix4 matrix;

    matrix.m_Column[0].x = right.x;
    matrix.m_Column[0].y = up.x;
    matrix.m_Column[0].z = -front.x;
    matrix.m_Column[0].w = 0.0f;

    matrix.m_Column[1].x = right.y;
    matrix.m_Column[1].y = up.y;
    matrix.m_Column[1].z = -front.y;
    matrix.m_Column[1].w = 0.0f;

    matrix.m_Column[2].x = right.z;
    matrix.m_Column[2].y = up.z;
    matrix.m_Column[2].z = -front.z;
    matrix.m_Column[2].w = 0.0f;

    matrix.m_Column[3].x = -right.Dot(position);
    matrix.m_Column[3].y = -up.Dot(position);
    matrix.m_Column[3].z = front.Dot(position);
    matrix.m_Column[3].w = 1.0f;

    return matrix;
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
    Matrix4 result;
    for (int col = 0; col < 4; col++)
    {
        const Vector4 &otherCol = other.m_Column[col];
        Vector4 newCol;

        newCol.x = m_Column[0].x * otherCol.x + m_Column[1].x * otherCol.y + m_Column[2].x * otherCol.z + m_Column[3].x * otherCol.w;
        newCol.y = m_Column[0].y * otherCol.x + m_Column[1].y * otherCol.y + m_Column[2].y * otherCol.z + m_Column[3].y * otherCol.w;
        newCol.z = m_Column[0].z * otherCol.x + m_Column[1].z * otherCol.y + m_Column[2].z * otherCol.z + m_Column[3].z * otherCol.w;
        newCol.w = m_Column[0].w * otherCol.x + m_Column[1].w * otherCol.y + m_Column[2].w * otherCol.z + m_Column[3].w * otherCol.w;

        result.m_Column[col] = newCol;
    }
    return result;
}

Matrix3 Matrix3::RotationAxis(const Vector3 &axis, float angle)
{
    Vector3 a = axis.Normalized();
    float x = a.x, y = a.y, z = a.z;

    float c = cos(angle);
    float s = sin(angle);
    float t = 1.0f - c;

    Matrix3 matrix;

    // First column (X axis)
    matrix.m_Column[0].x = t * x * x + c;
    matrix.m_Column[0].y = t * x * y + s * z;
    matrix.m_Column[0].z = t * x * z - s * y;

    // Second column (Y axis)
    matrix.m_Column[1].x = t * x * y - s * z;
    matrix.m_Column[1].y = t * y * y + c;
    matrix.m_Column[1].z = t * y * z + s * x;

    // Third column (Z axis)
    matrix.m_Column[2].x = t * x * z + s * y;
    matrix.m_Column[2].y = t * y * z - s * x;
    matrix.m_Column[2].z = t * z * z + c;

    return matrix;
}

Vector3 Matrix3::operator*(const Vector3 &vector)
{
    return Vector3(
        m_Column[0].x * vector.x + m_Column[1].x * vector.y + m_Column[2].x * vector.z,
        m_Column[0].y * vector.x + m_Column[1].y * vector.y + m_Column[2].y * vector.z,
        m_Column[0].z * vector.x + m_Column[1].z * vector.y + m_Column[2].z * vector.z);
}

Matrix4 Matrix4::operator=(const Matrix4 &other)
{
    Matrix4 matrix;
    m_Column[0] = other.m_Column[0];
    m_Column[1] = other.m_Column[1];
    m_Column[2] = other.m_Column[2];
    m_Column[3] = other.m_Column[3];

    return *this;
}
