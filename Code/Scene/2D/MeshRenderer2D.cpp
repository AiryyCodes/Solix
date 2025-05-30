#include "Scene/2D/MeshRenderer2D.h"
#include "Renderer/IRenderer.h"
#include "Scene/2D/Node2D.h"

void MeshRenderer2D::Render()
{
    Node2D::Render();

    IRenderer::Get().DrawArrays(m_Mesh);
}
