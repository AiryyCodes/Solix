#include "Renderer/OpenGL/OpenGLTexture.h"
#include "Core/Logger.h"
#include "Renderer/Texture.h"

#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_Id);
}

void OpenGLTexture::OnInit()
{
    glGenTextures(1, &m_Id);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    SetFilter(m_Filter);

    int width;
    int height;
    int numChannels;

    unsigned char *data = stbi_load(m_Path.c_str(), &width, &height, &numChannels, 0);
    if (data)
    {
        unsigned int format = GL_RGB;
        switch (numChannels)
        {
        case 1:
            GL_RED;
            break;
        case 2:
            GL_RG;
            break;
        case 3:
            GL_RGB;
            break;
        case 4:
            GL_RGBA;
            break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        if (m_Mipmap)
            glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOG_ERROR("Failed to load texture '{}'", m_Path);
    }

    stbi_image_free(data);
}

void OpenGLTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void OpenGLTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::SetFilter(TextureFilter filter)
{
    m_Filter = filter;

    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilter(filter, m_Mipmap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilter(filter, false));
}

unsigned int OpenGLTexture::GetOpenGLFilter(TextureFilter filter, bool mipmap)
{
    switch (filter)
    {
    case TextureFilter::Linear:
        return mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
    case TextureFilter::Nearest:
        return mipmap ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
    default:
        return mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
    }
}
