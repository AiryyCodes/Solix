#pragma once

#include "Renderer/Mesh.h"
#include "Scene/2D/Node2D.h"
#include "Scene/Node.h"

class MeshRenderer2D : public Node2D
{
    NODE_CLASS(MeshRenderer2D, Node2D);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Render() override;
    virtual void InspectorGUI() override {}

    void SetMesh(Mesh &mesh);

private:
    Mesh m_Mesh;
};
