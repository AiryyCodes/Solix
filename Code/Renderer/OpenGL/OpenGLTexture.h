#pragma once

#include "Renderer/Texture.h"
#include <string>

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(const std::string &path)
        : m_Path(path) {}
    ~OpenGLTexture();

    void OnInit() override;

    void Bind() override;
    void Unbind() override;

    bool IsMipmap() const override { return m_Mipmap; }
    void SetMipmap(bool mipmap) override { m_Mipmap = mipmap; }

    TextureFilter GetFilter() const override
    {
        return m_Filter;
    }
    void SetFilter(TextureFilter filter) override;

private:
    unsigned int GetOpenGLFilter(TextureFilter filter, bool mipmap);

private:
    std::string m_Path;

    TextureFilter m_Filter = TextureFilter::Linear;
    bool m_Mipmap = true;

    unsigned int m_Id = 0;
};
