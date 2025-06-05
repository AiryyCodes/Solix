#pragma once

#include "Core/Logger.h"

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
    }

class Node
{
public:
    explicit Node(const std::string &name)
        : m_Name(name) {}

    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}

    /* FOR CUSTOM INTERNAL LOGIC */
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
    /* FOR BASE NODE LOGIC */
    virtual void InitBase() {}
    virtual void UpdateBase() {}
    virtual void RenderBase() {}

    virtual bool ShouldRender() const { return true; }

    virtual std::string GetName() const { return m_Name; }

private:
    std::string m_Name;
};
