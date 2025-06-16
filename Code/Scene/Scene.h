#pragma once

#include "Core/Assert.h"
#include "Core/Base.h"
#include "Core/List.h"
#include "Scene/Node.h"

#include <string>
#include <type_traits>

class Scene
{
public:
    void OnInit();
    void OnUpdate();
    void OnRender();

    template <typename T>
    Ref<T> AddNode(const std::string &name)
    {
        STATIC_ASSERT((std::is_base_of_v<Node, T>), "T is not derived from Node");

        std::string newName = name;
        int numSimilarNames = GetNumSimilarNames(name);
        if (numSimilarNames >= 1)
        {
            newName.append(" #" + std::to_string(numSimilarNames + 1));
        }

        Ref<T> node = CreateRef<T>(newName);
        node->SetParent(nullptr);
        m_Nodes.Add(node);

        return node;
    }

    List<Ref<Node>> GetNodes() const { return m_Nodes; }

private:
    void Init(Ref<Node> node);
    void Update(Ref<Node> node);
    void Render(Ref<Node> node);

    int GetNumSimilarNames(const std::string &name);

private:
    List<Ref<Node>> m_Nodes;
};
