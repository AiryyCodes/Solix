#include "Renderer/Material.h"
#include "Renderer/IRenderer.h"

Material::Material()
{
    m_Texture = IRenderer::Get().CreateTexture("Resources/Textures/Null.png");
    m_Texture->OnInit();
}
