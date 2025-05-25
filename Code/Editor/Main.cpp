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

    Ref<IShader> shader = renderer->CreateShader();
    auto result = shader->OnInit("Resources/Shaders/Main.vert", "Resources/Shaders/Main.frag");
    if (result.HasValue())
    {
        LOG_ERROR(result.GetValue());
        return EXIT_FAILURE;
    }

    BufferLayout layout;
    layout.AddElement("a_Position", BufferDataType::Float3);

    Mesh mesh;
    mesh.SetVertices(QUAD_VERTICES);
    mesh.SetLayout(layout);

    Camera2D camera;

    Matrix4 transform = Matrix4::Identity();
    transform.Scale(Vector2(1.0f, 2.0f));
    transform.RotateZ(Math::ToRadians(15.0f));
    transform.Translate(Vector2(0.0f, 0.0f));

    while (!window->IsClosing())
    {
        renderer->Clear();
        renderer->ClearColor(Color(0, 0, 0, 255));
        renderer->SetViewport(window->GetWidth(), window->GetHeight(), 0, 0);

        shader->Bind();
        shader->SetUniform("u_Transform", transform);
        shader->SetUniform("u_View", camera.GetViewMatrix());
        shader->SetUniform("u_Projection", camera.GetProjectionMatrix());

        renderer->DrawArrays(mesh);

        window->PollEvents();
        window->SwapBuffers();
    }

    return EXIT_SUCCESS;
}
