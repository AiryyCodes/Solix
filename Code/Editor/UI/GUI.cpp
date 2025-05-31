#include "Editor/UI/GUI.h"
#include "Core/Logger.h"
#include "Scene/Scene.h"

#include <imgui.h>
#include <imgui_internal.h>

void GUI::Init()
{
}

void GUI::Render()
{
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Dockspace", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    ImGuiID dockspaceId = ImGui::GetID("MainDockspace");

    ImGuiDockNode *node = ImGui::DockBuilderGetNode(dockspaceId);
    bool has_layout = node && node->IsDockSpace();

    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    if (!has_layout)
    {
        ImGuiID hierarchyId = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.2f, nullptr, &dockspaceId);
        ImGuiID inspectorId = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Right, 0.25f, nullptr, &dockspaceId);

        ImGui::DockBuilderDockWindow("Main Window", dockspaceId);
        ImGui::DockBuilderDockWindow("Hierarchy", hierarchyId);
        ImGui::DockBuilderDockWindow("Inspector", inspectorId);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    ImGui::PopStyleVar(2);
    ImGui::End();

    Hierarchy();

    ImGui::Begin("Inspector");

    ImGui::End();

    // ImGui::ShowDemoWindow();
}

void GUI::Hierarchy()
{
    Scene *scene = m_State.scene;

    ;

    ImGui::Begin("Hierarchy");
    {
        for (const auto &node : scene->GetNodes())
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
            if (m_State.selectedNode == node.get())
                flags |= ImGuiTreeNodeFlags_Selected;

            bool isSelected = m_State.selectedNode == node.get();
            if (isSelected)
            {
                ImGui::PushStyleColor(ImGuiCol_Header, ImGui::GetColorU32(ImGuiCol_ButtonActive));
            }

            ImGui::PushID(node->GetName().c_str());

            bool open = ImGui::TreeNodeEx(node->GetName().c_str(), flags);

            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
            {
                m_State.selectedNode = node.get();
            }

            if (open)
            {
                ImGui::TreePop();
            }

            ImGui::PopID();

            if (isSelected)
                ImGui::PopStyleColor(1);
        }
    }
    ImGui::End();
}
