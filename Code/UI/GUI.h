#pragma once

#include "Scene/Scene.h"

struct UIState
{
    Scene *scene;

    Node *selectedNode = nullptr;
};

class GUI
{
public:
    GUI(UIState state)
        : m_State(state) {}

    void Init();
    void Render();

private:
    void Hierarchy();
    void Inspector();

private:
    UIState m_State;
};
