#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IWindow.h"

#include <GLFW/glfw3.h>
#include <string>

class Window : public IWindow
{
public:
    Window(int width, int height, const std::string &title);

    virtual Optional<Error> OnInit() override;

    virtual void PollEvents() const override { glfwPollEvents(); }
    virtual void SwapBuffers() const override { glfwSwapBuffers(m_Window); }

    virtual bool IsClosing() const override { return glfwWindowShouldClose(m_Window); }

private:
    GLFWwindow *m_Window;

    int m_Width;
    int m_Height;
    std::string m_Title;
};
