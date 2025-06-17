#pragma once

#include "Renderer/Mesh.h"
#include "Scene/3D/Node3D.h"

class MeshRenderer3D : public Node3D
{
    NODE_CLASS(MeshRenderer3D, Node3D);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Init() override { Node3D::Init(); }
    virtual void Render() override;
    virtual void InspectorGUI() override {}

    void SetMesh(Mesh &mesh);

private:
    Mesh m_Mesh;
};
