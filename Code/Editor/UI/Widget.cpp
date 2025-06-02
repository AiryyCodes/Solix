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
    float labelWidth = ImGui::CalcTextSize("X").x + ImGui::CalcTextSize("Y").x + spacing * 2;
    float inputWidth = (fullWidth - labelWidth - spacing * 2) * 0.5f;

    // X
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("X");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##X", &vector.x(), 0.1f);
    ImGui::PopItemWidth();

    ImGui::SameLine(0.0f, spacing * 2);

    // Y
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Y");
    ImGui::SameLine(0.0f, spacing * 2);
    ImGui::PushItemWidth(inputWidth);
    ImGui::DragFloat("##Y", &vector.y(), 0.1f);
    ImGui::PopItemWidth();

    ImGui::Columns(1);
    ImGui::PopID();
}
