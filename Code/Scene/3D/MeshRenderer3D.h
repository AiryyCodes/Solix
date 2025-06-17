#pragma once

#include "Core/Base.h"
#include "Renderer/IShader.h"
#include "Renderer/Mesh.h"
#include "Scene/3D/Node3D.h"

class MeshRenderer3D : public Node3D
{
    NODE_CLASS(MeshRenderer3D, Node3D);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Render() override;
    virtual void InspectorGUI() override {}

    void SetMesh(Mesh &mesh);
    void SetShader(Ref<IShader> shader);

private:
    Mesh m_Mesh;
    Ref<IShader> m_Shader;
};
