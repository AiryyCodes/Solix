#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Logger.h"
#include "Core/Math/Vector.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"
#include "Renderer/IWindow.h"
#include "Renderer/Mesh.h"

#include <cstdlib>

static List<Vector3> TRIANGLE_VERTICES = {
    Vector3(-0.5f, -0.5f, 0.0f),
    Vector3(0.5f, -0.5f, 0.0f),
    Vector3(0.0f, 0.5f, 0.0f),
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

    Mesh mesh;
    mesh.SetVertices(TRIANGLE_VERTICES);

    while (!window->IsClosing())
    {
        renderer->Clear();
        renderer->ClearColor(Color(0, 0, 0, 255));

        shader->Bind();
        renderer->DrawArrays(mesh);

        window->PollEvents();
        window->SwapBuffers();
    }

    return EXIT_SUCCESS;
}
