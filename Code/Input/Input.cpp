#include "Input/Input.h"

#include <array>

std::array<bool, static_cast<size_t>(Key::Count)> Input::m_Keys = {};
std::array<bool, static_cast<size_t>(Key::Count)> Input::m_KeysHeld = {};

void Input::KeyCallback(Key key, Action action)
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
