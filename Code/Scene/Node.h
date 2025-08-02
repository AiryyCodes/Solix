#pragma once

#include "Core/Base.h"
#include "Core/Assert.h"
#include "Core/List.h"
#include "Core/Math/Matrix.h"
#include "Core/Object.h"

#include <memory>
#include <string>

#define NODE_CLASS(CLASS_NAME, BASE_CLASS_NAME)                           \
public:                                                                   \
    static Object *CreateInstance() { return new CLASS_NAME("default"); } \
    const char *GetClassName() const override { return #CLASS_NAME; }     \
    static const char *GetBaseClassName() { return #BASE_CLASS_NAME; }    \
                                                                          \
public:                                                                   \
    CLASS_NAME(const std::string &name) : BASE_CLASS_NAME(name) {}

class Node : public Object
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
        m_Children.Add(node);
    }

    template <typename T>
    T *GetChild(const std::string &name)
    {
        for (const auto &child : m_Children)
        {
            if (auto derived = std::dynamic_pointer_cast<T>(child))
                return &derived;
        }

        return nullptr;
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

    /* FOR CUSTOM INTERNAL LOGIC */
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

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
