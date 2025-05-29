#pragma once

#include "Core/Base.h"
#include "Core/List.h"
#include "Scene/Node.h"
#include <string>

class Scene
{
public:
    void OnInit();
    void OnUpdate();
    void OnRender();

    template <typename T>
    Ref<T> AddNode(const std::string &name)
    {
        // TODO: Assert the template paremeter is derived from Node

        Ref<T> node = CreateRef<T>();
        m_Nodes.Add(node);

        return node;
    }

private:
    List<Ref<Node>> m_Nodes;
};
