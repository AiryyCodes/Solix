#include "Editor/UI/Widget.h"
#include "Core/Math/Vector.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <string>

void Widget::Vector2Input(const std::string &label, Vector2 &vector)
{
    ImGui::PushID(("Vector2Input" + label).c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.35f);

    ImGui::TextUnformatted(label.c_str());

    ImGui::NextColumn();

    float fullWidth = ImGui::GetContentRegionAvail().x;
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    float padding = ImGui::GetStyle().WindowPadding.x;
    float inputWidth = fullWidth - spacing - padding;

    // X
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("X");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##X", &vector.x, 0.1f);
    ImGui::PopItemWidth();

    // Y
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Y");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##Y", &vector.y, 0.1f);
    ImGui::PopItemWidth();

    ImGui::Columns(1);
    ImGui::PopID();
}

void Widget::Vector3Input(const std::string &label, Vector3 &vector)
{
    ImGui::PushID(("Vector2Input" + label).c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x * 0.35f);

    ImGui::TextUnformatted(label.c_str());

    ImGui::NextColumn();

    float fullWidth = ImGui::GetContentRegionAvail().x;
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    float padding = ImGui::GetStyle().WindowPadding.x;
    float inputWidth = fullWidth - spacing - padding;

    // X
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("X");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##X", &vector.x, 0.1f);
    ImGui::PopItemWidth();

    // Y
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Y");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##Y", &vector.y, 0.1f);
    ImGui::PopItemWidth();

    // Z
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Z");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##Z", &vector.z, 0.1f);
    ImGui::PopItemWidth();

    ImGui::Columns(1);
    ImGui::PopID();
}
