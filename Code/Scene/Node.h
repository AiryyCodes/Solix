#pragma once

#include <string>

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

    virtual const std::string &GetName() const { return m_Name; }

private:
    std::string m_Name;
};
