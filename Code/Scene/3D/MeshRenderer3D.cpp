#include "Scene/3D/MeshRenderer3D.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

void MeshRenderer3D::Render()
{
    // m_Shader->Bind();
    IRenderer::Get().DrawArrays(m_Mesh);
}

void MeshRenderer3D::SetMesh(Mesh &mesh)
{
    m_Mesh = mesh;
    m_Mesh.Init();
}

void MeshRenderer3D::SetShader(Ref<IShader> shader)
{
    m_Shader = shader;
}
