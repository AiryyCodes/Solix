#include "Scene/2D/MeshRenderer2D.h"
#include "Core/Logger.h"
#include "Renderer/IRenderer.h"

void MeshRenderer2D::Render()
{
    IRenderer::Get().DrawArrays(m_Mesh);
}
