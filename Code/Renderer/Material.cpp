#include "Renderer/Material.h"
#include "Renderer/IRenderer.h"

Material::Material()
{
    m_Texture = IRenderer::Get().CreateTexture("Solix/Resources/Textures/Null.png");
    m_Texture->SetMipmap(false);
    m_Texture->SetFilter(TextureFilter::Nearest);
    m_Texture->OnInit();
}
