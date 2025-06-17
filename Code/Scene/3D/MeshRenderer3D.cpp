#include "Scene/3D/MeshRenderer3D.h"
#include "Renderer/IRenderer.h"

void MeshRenderer3D::Render()
{
    Node3D::Render();

    GetShader()->Bind();
    IRenderer::Get().DrawArrays(m_Mesh);
}

void MeshRenderer3D::SetMesh(Mesh &mesh)
{
    m_Mesh = mesh;
    m_Mesh.Init();
}
