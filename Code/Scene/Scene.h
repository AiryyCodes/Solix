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

        std::string newName = name;
        int numSimilarNames = GetNumSimilarNames(name);
        if (numSimilarNames >= 1)
        {
            newName.append(" #" + std::to_string(numSimilarNames + 1));
        }

        Ref<T> node = CreateRef<T>(newName);
        m_Nodes.Add(node);

        return node;
    }

    List<Ref<Node>> GetNodes() const { return m_Nodes; }

private:
    int GetNumSimilarNames(const std::string &name);

private:
    List<Ref<Node>> m_Nodes;
};
