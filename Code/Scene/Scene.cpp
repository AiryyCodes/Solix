#include "Scene/Scene.h"

void Scene::OnInit()
{
    for (const auto &node : m_Nodes)
    {
        node->Init();
        node->OnInit();
    }
}

void Scene::OnUpdate()
{
    for (const auto &node : m_Nodes)
    {
        node->Update();
        node->OnUpdate();
    }
}

void Scene::OnRender()
{
    for (const auto &node : m_Nodes)
    {
        node->Render();
        node->OnRender();
    }
}
