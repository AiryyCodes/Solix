#include "Scene/3D/Node3D.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "UI/Widget.h"

#include <cmath>
#include <imgui.h>

void Node3D::Render()
{
    if (!ShouldRender())
        return;

    m_Shader->Bind();
    m_Shader->SetUniform("u_Transform", GetGlobalTransform());
}

void Node3D::InspectorGUI()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    ImGui::PushID("TransformComponent");
    if (ImGui::TreeNodeEx("Transform", flags))
    {
        Widget::Vector3Input("Position", GetPosition());
        Widget::Vector3Input("Scale", GetScale());
        Widget::Vector3Input("Rotation", GetRotation());

        ImGui::TreePop();
    }
    ImGui::PopID();
}

Matrix4 Node3D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);
    matrix.Scale(m_Scale);
    matrix.RotateZ(Math::ToRadians(m_Rotation.z));
    matrix.RotateY(Math::ToRadians(m_Rotation.y));
    matrix.RotateX(Math::ToRadians(m_Rotation.x));

    return matrix;
}

Matrix4 Node3D::GetGlobalTransform()
{
    if (!IsDirty())
        return m_GlobalTransform;

    if (GetParent())
    {
        m_GlobalTransform = GetParent()->GetGlobalTransform() * GetTransformMatrix();
    }
    else
    {
        m_GlobalTransform = GetTransformMatrix();
    }

    SetDirty(false);
    return m_GlobalTransform;
}

Vector3 Node3D::GetRight()
{
    Vector3 front = GetFront();
    Vector3 worldUp(0.0f, 1.0f, 0.0f);
    Vector3 right = front.Cross(worldUp).Normalized();

    // Apply roll around the front vector
    float roll = Math::ToRadians(m_Rotation.z);
    Matrix3 rollMatrix = Matrix3::RotationAxis(front, roll);

    return (rollMatrix * right).Normalized();
}

Vector3 Node3D::GetGlobalRight()
{
    return GetGlobalTransform()[0].GetXYZ().Normalized();
}

Vector3 Node3D::GetUp()
{
    Vector3 front = GetFront();
    Vector3 right = GetRight();

    return right.Cross(front).Normalized();
}

Vector3 Node3D::GetGlobalUp()
{
    return GetGlobalTransform()[1].GetXYZ().Normalized();
}

Vector3 Node3D::GetFront()
{
    float yaw = Math::ToRadians(m_Rotation.y);
    float pitch = Math::ToRadians(m_Rotation.x);

    Vector3 forward;
    forward.x = cos(pitch) * sin(yaw);
    forward.y = -sin(pitch);
    forward.z = -cos(pitch) * cos(yaw);

    return forward.Normalized();
}

Vector3 Node3D::GetGlobalFront()
{
    return GetGlobalTransform()[1].GetXYZ().Normalized();
}

Vector3 Node3D::GetGlobalPosition()
{
    Matrix4 global = GetGlobalTransform();
    return Vector3(global[3].x, global[3].y, global[3].z);
}

void Node3D::SetPosition(const Vector3 &position)
{
    m_Position = position;
    MarkDirty();
}

Vector3 Node3D::GetGlobalScale()
{
    Matrix4 global = GetGlobalTransform();
    return Vector3(global[0].x, global[1].y, global[2].z);
}

void Node3D::SetScale(const Vector3 &scale)
{
    m_Scale = scale;
    MarkDirty();
}

Vector3 Node3D::GetGlobalRotation()
{
    Matrix3 matrix = GetRotationMatrix(GetGlobalTransform());

    float sy = -matrix[0].z;
    float cy = std::sqrt(1.0f - sy * sy);

    Vector3 euler;

    if (cy > 1e-5)
    {
        euler.x = std::atan2(matrix[1].z, matrix[2].z); // pitch
        euler.y = std::asin(sy);                        // yaw
        euler.z = std::atan2(matrix[0].y, matrix[0].x); // roll
    }
    else
    {
        // Gimbal lock
        euler.x = 0.0f;
        euler.y = std::asin(sy);
        euler.z = std::atan2(-matrix[1].x, matrix[1].y);
    }

    return euler;
}

void Node3D::SetRotation(const Vector3 &rotation)
{
    m_Rotation = rotation;
    MarkDirty();
}

Matrix3 Node3D::GetRotationMatrix(const Matrix4 &matrix)
{
    return Matrix3(
        matrix.m_Column[0].GetXYZ(),
        matrix.m_Column[1].GetXYZ(),
        matrix.m_Column[2].GetXYZ());
}
