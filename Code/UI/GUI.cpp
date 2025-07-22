#include "UI/GUI.h"
#include "Core/Logger.h"
#include "Core/Object.h"
#include "Core/Variant.h"
#include "UI/Widget.h"
#include "Scene/2D/Node2D.h"
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

    ImGuiDockNodeFlags dockNodeFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    dockNodeFlags |= ImGuiDockNodeFlags_NoCloseButton;
    dockNodeFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;
    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockNodeFlags);

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
    Inspector();
}

void GUI::Hierarchy()
{
    Scene *scene = m_State.scene;

    ImGui::Begin("Hierarchy");
    {
        for (const auto &node : scene->GetNodes())
        {
            bool hasChildren = node->GetChildren().GetLength() > 0;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
            if (!hasChildren)
                flags |= ImGuiTreeNodeFlags_Leaf;

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
                HierarchyChildren(node);

                ImGui::TreePop();
            }

            ImGui::PopID();

            if (isSelected)
                ImGui::PopStyleColor(1);
        }
    }
    ImGui::End();
}

void GUI::HierarchyChildren(Ref<Node> node)
{
    for (const auto &child : node->GetChildren())
    {
        bool hasChildren = child->GetChildren().GetLength() > 0;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
        if (!hasChildren)
            flags |= ImGuiTreeNodeFlags_Leaf;

        if (m_State.selectedNode == child.get())
            flags |= ImGuiTreeNodeFlags_Selected;

        bool isSelected = m_State.selectedNode == child.get();
        if (isSelected)
        {
            ImGui::PushStyleColor(ImGuiCol_Header, ImGui::GetColorU32(ImGuiCol_ButtonActive));
        }

        ImGui::PushID(child->GetName().c_str());

        bool open = ImGui::TreeNodeEx(child->GetName().c_str(), flags);

        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            m_State.selectedNode = child.get();
        }

        if (open)
        {
            HierarchyChildren(child);
            ImGui::TreePop();
        }

        ImGui::PopID();

        if (isSelected)
            ImGui::PopStyleColor(1);
    }
}

void DrawPropertiesRecursive(Object *obj, const ClassInfo *info)
{
    if (!info)
        return;

    // Draw base class properties first
    if (!info->base.empty())
    {
        const ClassInfo *base_info = ClassDB::GetClass(info->base);
        DrawPropertiesRecursive(obj, base_info);
    }

    // Draw this class’s properties
    for (const auto &prop : info->properties)
    {
        Variant val = prop.getter(obj);

        // Example for int property
        if (val.GetType() == Variant::Int)
        {
            int v = val;
            if (ImGui::InputInt(prop.name.c_str(), &v))
            {
                prop.setter(obj, Variant(v));
            }
        }
        else if (val.GetType() == Variant::Float)
        {
            float v = val;
            LOG_INFO("Drawing property: {}", v);
            if (ImGui::DragFloat(prop.name.c_str(), &v))
            {
                prop.setter(obj, Variant(v));
            }
        }
        else if (val.GetType() == Variant::Vector2)
        {
            Vector2 vector = val;
            float v[2] = {vector.x, vector.y};

            // LOG_INFO("Drawing property: {}", v);
            if (ImGui::DragFloat2(prop.name.c_str(), v, 0.1f))
            {
                vector.x = v[0];
                vector.y = v[1];
                prop.setter(obj, Variant(vector));
            }
        }

        // Extend for float, bool, string, Vector2, etc.
        // For example:
        // else if (val.is_float()) { ... }
        // else if (val.is_bool()) { ... }
        // ...
    }
}

void InspectorDrawNode(Object *node)
{
    if (!node)
        return;

    const ClassInfo *info = ClassDB::GetClass(node->GetClassName());
    // LOG_INFO("Class Info: Class: {}", info->name);

    DrawPropertiesRecursive(node, info);
}

void GUI::Inspector()
{
    ImGui::Begin("Inspector");
    {
        if (!m_State.selectedNode)
        {
            ImGui::End();
            return;
        }

        Node *node = m_State.selectedNode;
        InspectorDrawNode(node);

        // node->InspectorGUI();
        // node->OnInspectorGUI();
    }
    ImGui::End();
}
