#pragma once

#include "Core/Base.h"
#include "Renderer/Texture.h"

class Material
{
public:
    Material();

    Ref<Texture> GetTexture() const { return m_Texture; }
    void SetTexture(Ref<Texture> texture) { m_Texture = texture; }

private:
    Ref<Texture> m_Texture;
};
