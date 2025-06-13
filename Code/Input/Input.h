#pragma once

#include <array>
#include <cstddef>

enum class Key
{
    Unknown,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,

    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    NumpadDecimal,
    NumpadDivide,
    NumpadMultiply,
    NumpadSubtract,
    NumpadAdd,
    NumpadEnter,
    NumpadEqual,

    Apostrophe,
    Comma,
    Minus,
    Period,
    Slash,
    Semicolon,
    Equal,
    LeftBracket,
    RightBracket,
    Grave,

    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    Right,
    Left,
    Down,
    Up,
    PageUp,
    PageDown,
    Home,
    End,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,

    Space,
    Shift,
    Control,
    Alt,
    Super,

    Count
};

enum class Action
{
    Unknown,
    Press,
    Release,
    Hold,

    Count
};

enum class CursorMode
{
    Locked,
    Unlocked,
    Hidden
};

class Input
{
public:
    static void OnKey(Key key, Action action);

    static bool IsKeyDown(Key key);
    static bool IsKeyHeld(Key key);

    static void OnMouseMove(float mouseX, float mouseY);

    static float GetMouseX();
    static float GetMouseY();
    static float GetMouseDeltaX();
    static float GetMouseDeltaY();

    static void SetCursorMode(CursorMode mode);
    static bool IsCursorLocked();

private:
    static std::array<bool, static_cast<size_t>(Key::Count)> m_Keys;
    static std::array<bool, static_cast<size_t>(Key::Count)> m_KeysHeld;

    static float m_MouseX;
    static float m_MouseY;
    static float m_MouseLastX;
    static float m_MouseLastY;

    static bool m_FirstMouse;

    static CursorMode m_CursorMode;
};
