#include "Editor/EditorRuntime.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Logger.h"
#include "UI/GUI.h"
#include "Renderer/Layout.h"
#include "Renderer/Mesh.h"
#include "Scene/2D/Camera2D.h"
#include "Scene/2D/MeshRenderer2D.h"
#include "Scene/3D/Camera3D.h"
#include "Scene/Scene.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

static List<Vector3> QUAD_VERTICES = {
    // Triangle 1
    Vector3(-0.5f, -0.5f, 0.0f),
    Vector3(0.5f, -0.5f, 0.0f),
    Vector3(-0.5f, 0.5f, 0.0f),
    // Triangle 2
    Vector3(0.5f, -0.5f, 0.0f),
    Vector3(-0.5f, 0.5f, 0.0f),
    Vector3(0.5f, 0.5f, 0.0f),
};

void EditorRuntime::OnInit()
{
    LOG_INFO("Starting editor...");

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    BufferLayout layout;
    layout.AddElement("a_Position", BufferDataType::Float3);

    Mesh mesh;
    mesh.SetVertices(QUAD_VERTICES);
    mesh.SetLayout(layout);

    Ref<Camera3D> camera = GetScene()->AddNode<Camera3D>("Camera3D");
    camera->SetPosition(Vector3(0.0f, 0.0f, 2.5f));

    Ref<MeshRenderer2D> meshRenderer = GetScene()->AddNode<MeshRenderer2D>("MeshRenderer2D");
    meshRenderer->SetMesh(mesh);

    Ref<MeshRenderer2D> meshRenderer2 = GetScene()->AddNode<MeshRenderer2D>("MeshRenderer2D");
    meshRenderer2->SetMesh(mesh);
    meshRenderer2->SetPosition(Vector2(1.0f, 1.0f));

    GetScene()->OnInit();

    UIState state;
    state.scene = GetScene().get();

    m_GUI = CreateRef<GUI>(state);

    m_GUI->Init();
}

void EditorRuntime::OnUpdate()
{
    m_GUI->Render();
}

void EditorRuntime::OnShutdown()
{
}

Ref<Runtime> StartRuntime()
{
    return CreateRef<EditorRuntime>();
}
