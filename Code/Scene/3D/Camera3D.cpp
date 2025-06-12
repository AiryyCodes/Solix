#include "Scene/3D/Camera3D.h"
#include "Core/Base.h"
#include "Core/Math/Math.h"
#include "Core/Runtime.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

#include <imgui.h>

void Camera3D::Render()
{
    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();

    mainShader->SetUniform("u_View", GetViewMatrix());
    mainShader->SetUniform("u_Projection", GetProjectionMatrix());
}

void Camera3D::InspectorGUI()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    ImGui::PushID("Camera3D");
    if (ImGui::TreeNodeEx("Camera3D", flags))
    {
        // Fov
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.325f);

        ImGui::TextUnformatted("FOV");

        ImGui::NextColumn();

        float fullWidth = ImGui::GetContentRegionAvail().x;
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        float padding = ImGui::GetStyle().WindowPadding.x;
        float inputWidth = fullWidth - spacing - padding + 15.0f;

        ImGui::PushItemWidth(inputWidth);
        ImGui::DragFloat("##FOV", &m_Fov);

        ImGui::Columns(1);

        // Near
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.325f);

        ImGui::TextUnformatted("Near");

        ImGui::NextColumn();

        ImGui::PushItemWidth(inputWidth);
        ImGui::DragFloat("##Near", &m_Near);

        ImGui::Columns(1);

        // Near
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.325f);

        ImGui::TextUnformatted("Far");

        ImGui::NextColumn();

        ImGui::PushItemWidth(inputWidth);
        ImGui::DragFloat("##Far", &m_Far);

        ImGui::Columns(1);

        ImGui::TreePop();
    }
    ImGui::PopID();
}

Matrix4 Camera3D::GetProjectionMatrix()
{
    Runtime &runtime = Runtime::Get();

    float aspect = (float)runtime.GetWindow()->GetWidth() / (float)runtime.GetWindow()->GetHeight();

    return Matrix4::Perspective(Math::ToRadians(m_Fov), aspect, m_Near, m_Far);
}

Matrix4 Camera3D::GetViewMatrix()
{
    Vector3 eye = GetGlobalPosition();
    Vector3 front = GetFront();
    Vector3 target = eye + front;
    Vector3 up = GetUp();

    return Matrix4::LookAt(eye, target, up);
}
