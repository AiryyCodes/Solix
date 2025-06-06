#include "Scene/3D/Node3D.h"
#include "Core/Base.h"
#include "Core/Logger.h"
#include "Core/Math/Math.h"
#include "Core/Math/Vector3.h"
#include "Editor/UI/Widget.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"
#include "Scene/3D/Camera3D.h"

#include <cmath>
#include <imgui.h>

void Node3D::Render()
{
    if (!ShouldRender())
        return;

    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();
    mainShader->SetUniform("u_Transform", GetTransformMatrix());
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

    matrix.RotateX(Math::ToRadians(m_Rotation.x));
    matrix.RotateY(Math::ToRadians(m_Rotation.y));
    matrix.RotateZ(Math::ToRadians(m_Rotation.z));

    matrix.Scale(m_Scale);

    return matrix;
}

Vector3 Node3D::GetUp() const
{
    Vector3 front = GetFront();
    Vector3 right = GetRight();

    return right.Cross(front).Normalized();
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
    Vector3 front = GetFront();
    Vector3 worldUp(0.0f, 1.0f, 0.0f);
    Vector3 right = front.Cross(worldUp).Normalized();

    // Apply roll around the front vector
    float roll = Math::ToRadians(m_Rotation.z);
    Matrix3 rollMatrix = Matrix3::RotationAxis(front, roll);

    return (rollMatrix * right).Normalized();
}
