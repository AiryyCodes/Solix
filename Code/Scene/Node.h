#pragma once

#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Math/Matrix.h"

#include <string>
#include <utility>

#define NODE_CLASS(NodeClass, BaseClass)                    \
public:                                                     \
    NodeClass(const std::string &name) : BaseClass(name) {} \
                                                            \
    void InitBase() override                                \
    {                                                       \
        BaseClass::Init();                                  \
    }                                                       \
    void UpdateBase() override                              \
    {                                                       \
        BaseClass::Update();                                \
    }                                                       \
    void RenderBase() override                              \
    {                                                       \
        BaseClass::Render();                                \
    }                                                       \
    void InspectorGUIBase() override                        \
    {                                                       \
        BaseClass::InspectorGUI();                          \
    }

class Node
{
public:
    explicit Node(const std::string &name)
        : m_Name(name) {}

    template <typename T>
    Ref<T> AddChild(const std::string &name)
    {
        STATIC_ASSERT((std::is_base_of_v<Node, T>), "T is not derived from Node");

        std::string newName = name;
        int numSimilarNames = GetNumSimilarNames(name);
        if (numSimilarNames >= 1)
        {
            newName.append(" #" + std::to_string(numSimilarNames + 1));
        }

        Ref<T> node = CreateRef<T>(newName);
        node->SetParent(this);
        m_Children.Add(node);

        return node;
    }

    void AddChild(Ref<Node> node)
    {
        node->SetParent(this);
        m_Children.Add(std::move(node));
    }

    Node *GetParent() { return m_Parent; }
    const Node *GetParent() const { return m_Parent; }
    void SetParent(Node *node)
    {
        m_Parent = node;
    }

    void MarkDirty()
    {
        if (m_Dirty)
            return;

        m_Dirty = true;
        for (const auto &child : m_Children)
        {
            child->MarkDirty();
        }
    }

    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}
    virtual void OnInspectorGUI() {}

    /* FOR CUSTOM INTERNAL LOGIC */
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void InspectorGUI() {}

    /* FOR BASE NODE LOGIC */
    virtual void InitBase() {}
    virtual void UpdateBase() {}
    virtual void RenderBase() {}
    virtual void InspectorGUIBase() {}

    virtual bool ShouldRender() const { return true; }

    virtual Matrix4 GetGlobalTransform() = 0;

    const std::string &GetName() const { return m_Name; }

    bool IsDirty() const { return m_Dirty; }
    void SetDirty(bool dirty) const { m_Dirty = dirty; }

    const List<Ref<Node>> &GetChildren() const { return m_Children; }

private:
    int GetNumSimilarNames(const std::string &name);

private:
    std::string m_Name;

    mutable bool m_Dirty = true;

    Node *m_Parent;
    List<Ref<Node>> m_Children;
};
