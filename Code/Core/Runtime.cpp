#include "Core/Runtime.h"
#include "Core/Base.h"
#include "Core/Logger.h"
#include "Renderer/OpenGL/OpenGLRenderer.h"
#include "Renderer/Window.h"

#include <cstdlib>

Runtime *Runtime::m_Instance = nullptr;

void Runtime::Init()
{
    m_Instance = this;

    LOG_INFO("Initializing renderer...");

    m_Renderer = CreateScope<OpenGLRenderer>();
    Optional<Error> error = m_Renderer->OnPreInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed pre-initialization of renderer.");
        return;
    }

    LOG_INFO("Creating window...");

    m_Window = CreateRef<Window>(1280, 720, "Solix Engine");
    error = m_Window->OnInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed to initialize window.");
        return;
    }

    LOG_INFO("Successfully created window!")

    error = m_Renderer->OnInit();
    if (error.HasValue())
    {
        LOG_ERROR("{}", error.GetValue().GetMessage());
        LOG_ERROR("Failed to initialize renderer.");
        return;
    }

    LOG_INFO("Successfully initialized renderer!")

    m_Scene = CreateRef<Scene>();

    OnInit();

    m_Scene->OnInit();
}

void Runtime::Update()
{
    m_Renderer->Clear();
    m_Renderer->ClearColor(Color(0, 0, 0, 255));
    m_Renderer->SetViewport(m_Window->GetWidth(), m_Window->GetHeight(), 0, 0);

    m_Renderer->OnFrameBegin();

    GetScene()->OnUpdate();

    OnUpdate();

    GetRenderer()->GetMainShader()->Bind();
    GetScene()->OnRender();

    GetRenderer()->OnFrameEnd();

    GetWindow()->PollEvents();
    GetWindow()->SwapBuffers();
}

void Runtime::Shutdown()
{
    m_Renderer->OnShutdown();
}

int main(int argc, char **argv)
{
    Ref<Runtime> runtime = StartRuntime();
    runtime->Init();

    while (!runtime->GetWindow()->IsClosing())
    {
        runtime->Update();
    }

    runtime->Shutdown();

    return EXIT_SUCCESS;
}
