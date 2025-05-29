#pragma once

class Node
{
public:
    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}

    /* FOR INTERNAL LOGIC */
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
};
