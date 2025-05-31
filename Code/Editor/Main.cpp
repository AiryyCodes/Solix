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
#include "imgui_internal.h"

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

        ImGui::Begin("Hierarchy");
        ImGui::End();

        ImGui::Begin("Inspector");

        ImGui::End();

        // ImGui::ShowDemoWindow();

        renderer->OnFrameEnd();

        window->PollEvents();
        window->SwapBuffers();
    }

    app->OnShutdown();

    return EXIT_SUCCESS;
}
