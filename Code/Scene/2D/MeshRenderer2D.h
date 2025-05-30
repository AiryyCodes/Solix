#pragma once

#include "Renderer/Mesh.h"
#include "Scene/2D/Node2D.h"

class MeshRenderer2D : public Node2D
{
public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    void Render() override;

    void SetMesh(const Mesh &mesh) { m_Mesh = mesh; }

private:
    Mesh m_Mesh;
};
