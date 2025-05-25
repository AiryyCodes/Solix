#include "Scene/2D/Node2D.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"

Matrix4 Node2D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);

    matrix.RotateZ(Math::ToRadians(m_Rotation));

    matrix.Scale(m_Scale);

    return matrix;
}
