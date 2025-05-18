#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Logger.h"
#include "Renderer/OpenGL/OpenGLRenderer.h"
#include "Renderer/Window.h"

Ref<Application> Application::m_Instance = nullptr;

Ref<Application> Application::Start()
{
    if (m_Instance)
    {
        return m_Instance;
    }

    m_Instance = CreateRef<Application>();
    m_Instance->OnInit();

    return m_Instance;
}

void Application::OnInit()
{
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

    m_Window = CreateScope<Window>(1280, 720, "Solix Engine");
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
}
