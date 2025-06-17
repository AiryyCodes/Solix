#pragma once

enum class TextureFilter
{
    Linear,
    Nearest
};

class Texture
{
public:
    virtual ~Texture() = default;

    virtual void OnInit() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual bool IsMipmap() const = 0;
    virtual void SetMipmap(bool mipmap) = 0;

    virtual TextureFilter GetFilter() const = 0;
    virtual void SetFilter(TextureFilter filter) = 0;
};
