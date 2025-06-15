#include "Scene/3D/MeshRenderer3D.h"
#include "Renderer/IRenderer.h"

void MeshRenderer3D::Render()
{
    IRenderer::Get().DrawArrays(m_Mesh);
}
