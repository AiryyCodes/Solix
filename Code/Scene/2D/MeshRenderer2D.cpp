#include "Scene/2D/MeshRenderer2D.h"
#include "Renderer/IRenderer.h"

void MeshRenderer2D::Render()
{
    GetShader()->Bind();
    IRenderer::Get().DrawArrays(m_Mesh);
}

void MeshRenderer2D::SetMesh(Mesh &mesh)
{
    m_Mesh = mesh;
    mesh.Init();
}
