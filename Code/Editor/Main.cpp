#include "Core/Base.h"
#include "Core/Logger.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IWindow.h"
#include "Renderer/OpenGL/OpenGLRenderer.h"
#include "Renderer/Window.h"

int main()
{
    LOG_INFO("Starting editor...");

    LOG_INFO("Initializing renderer...");

    Scope<IRenderer> renderer = CreateScope<OpenGLRenderer>();
    Optional<Error> error = renderer->OnPreInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed pre-initialization of renderer.");
        return EXIT_FAILURE;
    }

    LOG_INFO("Creating window...");

    Scope<IWindow> window = CreateScope<Window>(1280, 720, "Solix Engine");
    error = window->OnInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed to initialize window.");
        return EXIT_FAILURE;
    }

    LOG_INFO("Successfully created window!")

    error = renderer->OnInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed to initialize renderer.");
        return EXIT_FAILURE;
    }

    LOG_INFO("Successfully initialized renderer!")

    LOG_INFO("Editor started successfully!");

    while (!window->IsClosing())
    {
        renderer->Clear();
        renderer->ClearColor(Color(0, 0, 0, 255));

        window->PollEvents();
        window->SwapBuffers();
    }

    return EXIT_SUCCESS;
}
