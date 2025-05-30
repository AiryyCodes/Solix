#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Logger.h"
#include "Core/Math/Vector.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IWindow.h"
#include "Renderer/Layout.h"
#include "Renderer/Mesh.h"
#include "Scene/2D/Camera2D.h"
#include "Scene/2D/MeshRenderer2D.h"
#include "Scene/Scene.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <cstdlib>

static List<Vector3> TRIANGLE_VERTICES = {
    Vector3(-0.5f, -0.5f, 0.0f),
    Vector3(0.5f, -0.5f, 0.0f),
    Vector3(0.0f, 0.5f, 0.0f),
};

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

int main()
{
    LOG_INFO("Starting editor...");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Ref<Application> app = Application::Start();

    LOG_INFO("Editor started successfully!");

    Ref<IWindow> window = app->GetWindow();
    Ref<IRenderer> renderer = app->GetRenderer();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    BufferLayout layout;
    layout.AddElement("a_Position", BufferDataType::Float3);

    Mesh mesh;
    mesh.SetVertices(QUAD_VERTICES);
    mesh.SetLayout(layout);

    Scene scene;

    Ref<Camera2D> camera = scene.AddNode<Camera2D>("Camera2D");

    Ref<MeshRenderer2D> meshRenderer = scene.AddNode<MeshRenderer2D>("MeshRenderer2D");
    meshRenderer->SetMesh(mesh);

    Ref<MeshRenderer2D> meshRenderer2 = scene.AddNode<MeshRenderer2D>("MeshRenderer2D");
    meshRenderer2->SetMesh(mesh);
    meshRenderer2->SetPosition(Vector2(1.0f, 1.0f));

    scene.OnInit();

    while (!window->IsClosing())
    {
        renderer->Clear();
        renderer->ClearColor(Color(0, 0, 0, 255));
        renderer->SetViewport(window->GetWidth(), window->GetHeight(), 0, 0);

        renderer->OnFrameBegin();

        scene.OnUpdate();

        renderer->GetMainShader()->Bind();
        scene.OnRender();

        ImGui::ShowDemoWindow();

        renderer->OnFrameEnd();

        window->PollEvents();
        window->SwapBuffers();
    }

    app->OnShutdown();

    return EXIT_SUCCESS;
}
