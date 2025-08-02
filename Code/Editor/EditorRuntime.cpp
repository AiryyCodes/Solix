#include "Editor/EditorRuntime.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Logger.h"
#include "Core/Math/Vector2.h"
#include "Core/Object.h"
#include "Renderer/IRenderer.h"
#include "UI/GUI.h"
#include "Renderer/Layout.h"
#include "Renderer/Mesh.h"
#include "Scene/2D/Camera2D.h"
#include "Scene/2D/MeshRenderer2D.h"

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

    REGISTER_CLASS(Camera2D, Node2D);
    REGISTER_CLASS(Node2D, Node);
    REGISTER_CLASS(MeshRenderer2D, Node2D);

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    BufferLayout layout;
    layout.AddElement("a_Position", BufferDataType::Float3);

    Mesh mesh;
    mesh.SetVertices(QUAD_VERTICES);
    // mesh.SetLayout(layout);

    Ref<Camera2D> camera = GetScene()->AddNode<Camera2D>("Camera2D");
    camera->SetPosition(Vector2(0.0f, 0.0f));

    Ref<MeshRenderer2D> meshRenderer = GetScene()->AddNode<MeshRenderer2D>("MeshRenderer2D");
    meshRenderer->SetMesh(mesh);
    meshRenderer->SetPosition(Vector2(0.0f, 0.0f));

    Ref<MeshRenderer2D> meshRenderer2 = meshRenderer->AddChild<MeshRenderer2D>("MeshRenderer2D (Child)");
    meshRenderer2->SetMesh(mesh);
    meshRenderer2->SetPosition(Vector2(1.0f, 1.0f));

    Ref<MeshRenderer2D> meshRenderer3 = meshRenderer2->AddChild<MeshRenderer2D>("MeshRenderer2D (Child)");
    meshRenderer3->SetMesh(mesh);
    meshRenderer3->SetPosition(Vector2(1.0f, 1.0f));

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
