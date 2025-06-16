#include "Scene/Scene.h"

void Scene::OnInit()
{
    for (const auto &node : m_Nodes)
    {
        Init(node);
    }
}

void Scene::OnUpdate()
{
    for (const auto &node : m_Nodes)
    {
        Update(node);
    }
}

void Scene::OnRender()
{
    for (const auto &node : m_Nodes)
    {
        Render(node);
    }
}

void Scene::Init(Ref<Node> node)
{
    node->InitBase();
    node->Init();
    node->OnInit();

    for (const auto &child : node->GetChildren())
    {
        Init(child);
    }
}

void Scene::Update(Ref<Node> node)
{
    node->UpdateBase();
    node->Update();
    node->OnUpdate();

    for (const auto &child : node->GetChildren())
    {
        Update(child);
    }
}

void Scene::Render(Ref<Node> node)
{
    node->RenderBase();
    node->Render();
    node->OnRender();

    for (const auto &child : node->GetChildren())
    {
        Render(child);
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
