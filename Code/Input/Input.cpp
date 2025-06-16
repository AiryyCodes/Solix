#include "Input/Input.h"
#include "Core/Base.h"
#include "Core/Runtime.h"
#include "Renderer/IWindow.h"

#include <array>

std::array<bool, static_cast<size_t>(Key::Count)> Input::m_Keys = {};
std::array<bool, static_cast<size_t>(Key::Count)> Input::m_KeysHeld = {};

float Input::m_MouseX = 0.0f;
float Input::m_MouseY = 0.0f;
float Input::m_MouseLastX = 0.0f;
float Input::m_MouseLastY = 0.0f;

bool Input::m_FirstMouse = true;

CursorMode Input::m_CursorMode = CursorMode::Unlocked;

void Input::OnKey(Key key, Action action)
{
    if (static_cast<size_t>(key) < static_cast<size_t>(Key::Count))
    {
        m_Keys[static_cast<size_t>(key)] = action == Action::Press;
        m_KeysHeld[static_cast<size_t>(key)] = action == Action::Press || action == Action::Hold;
    }
}

bool Input::IsKeyDown(Key key)
{
    return m_Keys[static_cast<size_t>(key)];
}

bool Input::IsKeyHeld(Key key)
{
    return m_KeysHeld[static_cast<size_t>(key)];
}

void Input::OnMouseMove(float mouseX, float mouseY)
{
    m_MouseX = mouseX;
    m_MouseY = mouseY;

    if (m_FirstMouse)
    {
        m_MouseLastX = m_MouseX;
        m_MouseLastY = m_MouseY;
        m_FirstMouse = false;
    }
}

float Input::GetMouseX()
{
    return m_MouseX;
}

float Input::GetMouseY()
{
    return m_MouseY;
}

float Input::GetMouseDeltaX()
{
    float deltaX = m_MouseX - m_MouseLastX;
    m_MouseLastX = m_MouseX;
    return deltaX;
}

float Input::GetMouseDeltaY()
{
    float deltaY = m_MouseLastY - m_MouseY;
    m_MouseLastY = m_MouseY;
    return deltaY;
}

void Input::SetCursorMode(CursorMode mode)
{
    Ref<IWindow> window = Runtime::Get().GetWindow();
    window->SetCursorMode(mode);
}

bool Input::IsCursorLocked()
{
    return m_CursorMode == CursorMode::Locked;
}
