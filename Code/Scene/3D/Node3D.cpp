#include "Scene/3D/Node3D.h"
#include "Core/Base.h"
#include "Core/Logger.h"
#include "Core/Math/Math.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"
#include "Scene/3D/Camera3D.h"

#include <cmath>

void Node3D::Render()
{
    if (!ShouldRender())
        return;

    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();
    mainShader->SetUniform("u_Transform", GetTransformMatrix());
}

Matrix4 Node3D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);

    matrix.RotateX(Math::ToRadians(m_Rotation.x));
    matrix.RotateY(Math::ToRadians(m_Rotation.y));
    matrix.RotateZ(Math::ToRadians(m_Rotation.z));

    matrix.Scale(m_Scale);

    return matrix;
}

Vector3 Node3D::GetUp() const
{
    float yaw = Math::ToRadians(m_Rotation.y);
    float pitch = Math::ToRadians(m_Rotation.x);

    Vector3 up;
    up.x = sin(pitch) * sin(yaw);
    up.y = cos(pitch);
    up.z = sin(pitch) * cos(yaw);

    return up;
}

Vector3 Node3D::GetFront() const
{
    float yaw = Math::ToRadians(m_Rotation.y);
    float pitch = Math::ToRadians(m_Rotation.x);

    Vector3 forward;
    forward.x = cos(pitch) * sin(yaw);
    forward.y = -sin(pitch);
    forward.z = -cos(pitch) * cos(yaw);

    return forward;
}

Vector3 Node3D::GetRight() const
{
    float yaw = Math::ToRadians(m_Rotation.y);
    float pitch = Math::ToRadians(m_Rotation.x);

    Vector3 right;
    right.x = cos(yaw);
    right.y = 0;
    right.z = -sin(yaw);

    return right;
}
