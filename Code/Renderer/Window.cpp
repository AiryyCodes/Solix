#include "Renderer/Window.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>

Window::Window(int width, int height, const std::string &title)
    : m_Width(width), m_Height(height), m_Title(title)
{
}

Optional<Error> Window::OnInit()
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        return Optional<Error>(Error("Failed to create GLFW window."));
    }

    glfwMakeContextCurrent(m_Window);

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);

    return Optional<Error>::Empty();
}

int Window::GetWidth() const
{
    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);
    return width;
}

void Window::SetWidth(int width)
{
    int currentWidth, currentHeight;
    glfwGetWindowSize(m_Window, &currentWidth, &currentHeight);
    glfwSetWindowSize(m_Window, width, currentHeight);
}

int Window::GetHeight() const
{
    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);
    return height;
}

void Window::SetHeight(int height)
{
    int currentWidth, currentHeight;
    glfwGetWindowSize(m_Window, &currentWidth, &currentWidth);
    glfwSetWindowSize(m_Window, currentWidth, height);
}
