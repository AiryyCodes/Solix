#include "Renderer/Window.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Input/Input.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>

Key glfwToKey(int key);
Action glfwToAction(int action);

int GetGLFWCursorMode(CursorMode mode);

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

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        return Optional<Error>(Error("Failed to create GLFW window."));
    }

    glfwMakeContextCurrent(m_Window);

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       { Input::OnKey(glfwToKey(key), glfwToAction(action)); });
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *, double mouseX, double mouseY)
                             { Input::OnMouseMove(static_cast<float>(mouseX), static_cast<float>(mouseY)); });

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

int Window::GetFrameBufferWidth() const
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return width;
}

int Window::GetFrameBufferHeight() const
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return height;
}

void Window::SetCursorMode(CursorMode mode)
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GetGLFWCursorMode(mode));
}

int GetGLFWCursorMode(CursorMode mode)
{
    switch (mode)
    {
    case CursorMode::Locked:
        return GLFW_CURSOR_DISABLED;
    case CursorMode::Unlocked:
        return GLFW_CURSOR_NORMAL;
    case CursorMode::Hidden:
        return GLFW_CURSOR_HIDDEN;
    }
}

Key glfwToKey(int key)
{
    switch (key)
    {
    case GLFW_KEY_A:
        return Key::A;
    case GLFW_KEY_B:
        return Key::B;
    case GLFW_KEY_C:
        return Key::C;
    case GLFW_KEY_D:
        return Key::D;
    case GLFW_KEY_E:
        return Key::E;
    case GLFW_KEY_F:
        return Key::F;
    case GLFW_KEY_G:
        return Key::G;
    case GLFW_KEY_H:
        return Key::H;
    case GLFW_KEY_I:
        return Key::I;
    case GLFW_KEY_J:
        return Key::J;
    case GLFW_KEY_K:
        return Key::K;
    case GLFW_KEY_L:
        return Key::L;
    case GLFW_KEY_M:
        return Key::M;
    case GLFW_KEY_N:
        return Key::N;
    case GLFW_KEY_O:
        return Key::O;
    case GLFW_KEY_P:
        return Key::P;
    case GLFW_KEY_Q:
        return Key::Q;
    case GLFW_KEY_R:
        return Key::R;
    case GLFW_KEY_S:
        return Key::S;
    case GLFW_KEY_T:
        return Key::T;
    case GLFW_KEY_U:
        return Key::U;
    case GLFW_KEY_V:
        return Key::V;
    case GLFW_KEY_W:
        return Key::W;
    case GLFW_KEY_X:
        return Key::X;
    case GLFW_KEY_Y:
        return Key::Y;
    case GLFW_KEY_Z:
        return Key::Z;
    case GLFW_KEY_0:
        return Key::Zero;
    case GLFW_KEY_1:
        return Key::One;
    case GLFW_KEY_2:
        return Key::Two;
    case GLFW_KEY_3:
        return Key::Three;
    case GLFW_KEY_4:
        return Key::Four;
    case GLFW_KEY_5:
        return Key::Five;
    case GLFW_KEY_6:
        return Key::Six;
    case GLFW_KEY_7:
        return Key::Seven;
    case GLFW_KEY_8:
        return Key::Eight;
    case GLFW_KEY_9:
        return Key::Nine;
    case GLFW_KEY_SPACE:
        return Key::Space;
    case GLFW_KEY_APOSTROPHE:
        return Key::Apostrophe;
    case GLFW_KEY_COMMA:
        return Key::Comma;
    case GLFW_KEY_MINUS:
        return Key::Minus;
    case GLFW_KEY_PERIOD:
        return Key::Period;
    case GLFW_KEY_SLASH:
        return Key::Slash;
    case GLFW_KEY_SEMICOLON:
        return Key::Semicolon;
    case GLFW_KEY_EQUAL:
        return Key::Equal;
    case GLFW_KEY_LEFT_BRACKET:
        return Key::LeftBracket;
    case GLFW_KEY_RIGHT_BRACKET:
        return Key::RightBracket;
    case GLFW_KEY_GRAVE_ACCENT:
        return Key::Grave;
    case GLFW_KEY_ESCAPE:
        return Key::Escape;
    case GLFW_KEY_ENTER:
        return Key::Enter;
    case GLFW_KEY_TAB:
        return Key::Tab;
    case GLFW_KEY_BACKSPACE:
        return Key::Backspace;
    case GLFW_KEY_INSERT:
        return Key::Insert;
    case GLFW_KEY_DELETE:
        return Key::Delete;
    case GLFW_KEY_LEFT:
        return Key::Left;
    case GLFW_KEY_RIGHT:
        return Key::Right;
    case GLFW_KEY_UP:
        return Key::Up;
    case GLFW_KEY_DOWN:
        return Key::Down;
    case GLFW_KEY_PAGE_UP:
        return Key::PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return Key::PageDown;
    case GLFW_KEY_HOME:
        return Key::Home;
    case GLFW_KEY_END:
        return Key::End;
    case GLFW_KEY_CAPS_LOCK:
        return Key::CapsLock;
    case GLFW_KEY_SCROLL_LOCK:
        return Key::ScrollLock;
    case GLFW_KEY_NUM_LOCK:
        return Key::NumLock;
    case GLFW_KEY_PRINT_SCREEN:
        return Key::PrintScreen;
    case GLFW_KEY_PAUSE:
        return Key::Pause;
    case GLFW_KEY_F1:
        return Key::F1;
    case GLFW_KEY_F2:
        return Key::F2;
    case GLFW_KEY_F3:
        return Key::F3;
    case GLFW_KEY_F4:
        return Key::F4;
    case GLFW_KEY_F5:
        return Key::F5;
    case GLFW_KEY_F6:
        return Key::F6;
    case GLFW_KEY_F7:
        return Key::F7;
    case GLFW_KEY_F8:
        return Key::F8;
    case GLFW_KEY_F9:
        return Key::F9;
    case GLFW_KEY_F10:
        return Key::F10;
    case GLFW_KEY_F11:
        return Key::F11;
    case GLFW_KEY_F12:
        return Key::F12;
    case GLFW_KEY_F13:
        return Key::F13;
    case GLFW_KEY_F14:
        return Key::F14;
    case GLFW_KEY_F15:
        return Key::F15;
    case GLFW_KEY_F16:
        return Key::F16;
    case GLFW_KEY_F17:
        return Key::F17;
    case GLFW_KEY_F18:
        return Key::F18;
    case GLFW_KEY_F19:
        return Key::F19;
    case GLFW_KEY_F20:
        return Key::F20;
    case GLFW_KEY_F21:
        return Key::F21;
    case GLFW_KEY_F22:
        return Key::F22;
    case GLFW_KEY_F23:
        return Key::F23;
    case GLFW_KEY_F24:
        return Key::F24;
    case GLFW_KEY_F25:
        return Key::F25;
    case GLFW_KEY_KP_0:
        return Key::Numpad0;
    case GLFW_KEY_KP_1:
        return Key::Numpad1;
    case GLFW_KEY_KP_2:
        return Key::Numpad2;
    case GLFW_KEY_KP_3:
        return Key::Numpad3;
    case GLFW_KEY_KP_4:
        return Key::Numpad4;
    case GLFW_KEY_KP_5:
        return Key::Numpad5;
    case GLFW_KEY_KP_6:
        return Key::Numpad6;
    case GLFW_KEY_KP_7:
        return Key::Numpad7;
    case GLFW_KEY_KP_8:
        return Key::Numpad8;
    case GLFW_KEY_KP_9:
        return Key::Numpad9;
    case GLFW_KEY_KP_DECIMAL:
        return Key::NumpadDecimal;
    case GLFW_KEY_KP_DIVIDE:
        return Key::NumpadDivide;
    case GLFW_KEY_KP_MULTIPLY:
        return Key::NumpadMultiply;
    case GLFW_KEY_KP_SUBTRACT:
        return Key::NumpadSubtract;
    case GLFW_KEY_KP_ADD:
        return Key::NumpadAdd;
    case GLFW_KEY_KP_ENTER:
        return Key::NumpadEnter;
    case GLFW_KEY_KP_EQUAL:
        return Key::NumpadEqual;
    case GLFW_KEY_LEFT_SHIFT:
        return Key::Shift;
    case GLFW_KEY_LEFT_CONTROL:
        return Key::Control;
    case GLFW_KEY_LEFT_ALT:
        return Key::Alt;
    case GLFW_KEY_LEFT_SUPER:
        return Key::Super;
    case GLFW_KEY_RIGHT_SHIFT:
        return Key::Shift;
    case GLFW_KEY_RIGHT_CONTROL:
        return Key::Control;
    case GLFW_KEY_RIGHT_ALT:
        return Key::Alt;
    case GLFW_KEY_RIGHT_SUPER:
        return Key::Super;
    default:
        return Key::Unknown;
    }
}

Action glfwToAction(int action)
{
    switch (action)
    {
    case GLFW_PRESS:
        return Action::Press;
    case GLFW_RELEASE:
        return Action::Release;
    case GLFW_REPEAT:
        return Action::Hold;
    default:
        return Action::Unknown;
    }
}
