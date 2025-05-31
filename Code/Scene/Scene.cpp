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

int Scene::GetNumSimilarNames(const std::string &name)
{
    int names = 0;
    for (int i = 0; i < m_Nodes.GetLength(); i++)
    {
        Ref<Node> node = m_Nodes.Get(i);
        if (node->GetName() == name)
        {
            names++;
        }
    }

    return names;
}
