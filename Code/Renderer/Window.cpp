#include "Renderer/Window.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <GLFW/glfw3.h>

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

    return Optional<Error>::Empty();
}
