#include "Scene/2D/Node2D.h"
#include "Core/Logger.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector2.h"
#include "UI/Widget.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

#include <imgui.h>

void Node2D::Render()
{
    if (!ShouldRender())
        return;

    // Ref<IShader> mainShader = IRenderer::Get().GetMainShader();
    GetShader()->Bind();
    GetShader()->SetUniform("u_Transform", GetGlobalTransform());
}

void Node2D::InspectorGUI()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    ImGui::PushID("TransformComponent");
    if (ImGui::TreeNodeEx("Transform", flags))
    {
        Widget::Vector2Input("Position", GetPosition());
        Widget::Vector2Input("Scale", GetScale());

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.325f);

        ImGui::TextUnformatted("Rotation");

        ImGui::NextColumn();

        float fullWidth = ImGui::GetContentRegionAvail().x;
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        float padding = ImGui::GetStyle().WindowPadding.x;
        float inputWidth = fullWidth - spacing - padding + 15.0f;

        ImGui::PushItemWidth(inputWidth);
        ImGui::DragFloat("##Rotation", &GetRotation());

        ImGui::Columns(1);
        ImGui::TreePop();
    }
    ImGui::PopID();

    MarkDirty();
}

Matrix4 Node2D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);

    matrix.RotateZ(Math::ToRadians(-m_Rotation));

    matrix.Scale(m_Scale);

    return matrix;
}

Matrix4 Node2D::GetGlobalTransform()
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

Vector2 Node2D::GetGlobalPosition()
{
    Matrix4 global = GetGlobalTransform();
    return Vector2(global[3].x, global[3].y);
}

void Node2D::SetPosition(const Vector2 &position)
{
    m_Position = position;
    MarkDirty();
}

Vector2 Node2D::GetGlobalScale()
{
    Matrix4 global = GetGlobalTransform();
    return Vector2(global[0].x, global[1].y);
}

void Node2D::SetScale(const Vector2 &scale)
{
    m_Scale = scale;
    MarkDirty();
}

float Node2D::GetGlobalRotation()
{
    Matrix3 matrix = GetRotationMatrix(GetGlobalTransform());

    float sy = -matrix[0].z;
    float cy = std::sqrt(1.0f - sy * sy);

    Vector3 euler;

    if (cy > 1e-5)
    {
        // euler.x = std::atan2(matrix[1].z, matrix[2].z); // pitch
        // euler.y = std::asin(sy);                        // yaw
        euler.z = std::atan2(matrix[0].y, matrix[0].x); // roll
    }
    else
    {
        // Gimbal lock
        // euler.x = 0.0f;
        // euler.y = std::asin(sy);
        euler.z = std::atan2(-matrix[1].x, matrix[1].y);
    }

    return euler.z;
}

void Node2D::SetRotation(float rotation)
{
    m_Rotation = rotation;
    MarkDirty();
}

Matrix3 Node2D::GetRotationMatrix(const Matrix4 &matrix)
{
    return Matrix3(
        matrix.m_Column[0].GetXYZ(),
        matrix.m_Column[1].GetXYZ(),
        matrix.m_Column[2].GetXYZ());
}
