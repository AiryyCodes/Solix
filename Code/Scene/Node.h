#pragma once

#include <string>

#define NODE_CLASS(NodeClass, BaseClass) \
public:                                  \
    NodeClass(const std::string &name) : BaseClass(name) {}

class Node
{
public:
    Node(const std::string &name)
        : m_Name(name) {}

    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}

    /* FOR INTERNAL LOGIC */
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    virtual std::string GetName() const { return m_Name; }

private:
    std::string m_Name;
};
