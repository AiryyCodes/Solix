#include "Scene/2D/Node2D.h"
#include "Core/Logger.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"
#include "UI/Widget.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

#include <imgui.h>

void Node2D::Render()
{
    if (!ShouldRender())
        return;

    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();
    mainShader->SetUniform("u_Transform", GetTransformMatrix());
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
}

Matrix4 Node2D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);

    matrix.RotateZ(Math::ToRadians(-m_Rotation));

    matrix.Scale(m_Scale);

    return matrix;
}
