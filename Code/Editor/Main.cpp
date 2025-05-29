#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Logger.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"
#include "Renderer/IWindow.h"
#include "Renderer/Layout.h"
#include "Renderer/Mesh.h"
#include "Scene/2D/Camera2D.h"
#include "Scene/Scene.h"

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

    Ref<Application> app = Application::Start();

    LOG_INFO("Editor started successfully!");

    Ref<IWindow> window = app->GetWindow();
    Ref<IRenderer> renderer = app->GetRenderer();

    BufferLayout layout;
    layout.AddElement("a_Position", BufferDataType::Float3);

    Mesh mesh;
    mesh.SetVertices(QUAD_VERTICES);
    mesh.SetLayout(layout);

    Scene scene;

    Ref<Camera2D> camera = scene.AddNode<Camera2D>("Camera2D");

    Matrix4 transform = Matrix4::Identity();
    transform.Scale(Vector2(1.0f, 1.0f));
    transform.RotateZ(Math::ToRadians(0.0f));
    transform.Translate(Vector2(0.0f, 0.0f));

    scene.OnInit();

    while (!window->IsClosing())
    {
        renderer->Clear();
        renderer->ClearColor(Color(0, 0, 0, 255));
        renderer->SetViewport(window->GetWidth(), window->GetHeight(), 0, 0);

        scene.OnUpdate();

        renderer->GetMainShader()->Bind();
        scene.OnRender();

        renderer->GetMainShader()->SetUniform("u_Transform", transform);

        renderer->DrawArrays(mesh);

        window->PollEvents();
        window->SwapBuffers();
    }

    app->OnShutdown();

    return EXIT_SUCCESS;
}
