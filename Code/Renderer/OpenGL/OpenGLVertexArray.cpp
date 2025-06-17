#include "Renderer/OpenGL/OpenGLVertexArray.h"
#include "Core/Logger.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Core/Assert.h"
#include "Renderer/Layout.h"

#include <cstddef>
#include <cstdint>
#include <glad/gl.h>

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteBuffers(1, &m_Id);
}

Optional<Error> OpenGLVertexArray::OnInit()
{
    glGenVertexArrays(1, &m_Id);

    return Optional<Error>::Empty();
}

void OpenGLVertexArray::Bind()
{
    glBindVertexArray(m_Id);
}

void OpenGLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::SetLayout(const BufferLayout &layout)
{
    Bind();

    for (unsigned int i = 0; i < layout.GetElements().GetLength(); i++)
    {
        const BufferElement &element = layout.GetElements().Get(i);

        // Should not be possible
        ASSERT(layout.GetComponents(element.GetType()) != 0, "Invalid element type (Components: 0)");
        ASSERT(GetGLType(element.GetType()) != GL_FALSE, "Invalid OpenGL element type");

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            layout.GetComponents(element.GetType()),
            GetGLType(element.GetType()),
            GL_FALSE,
            layout.GetStride(),
            (const void *)element.GetOffset());
    }

    m_Layout = layout;
}

void OpenGLVertexArray::EnableAttribute(unsigned int index, const BufferElement &element, int stride)
{
    // Should not be possible
    ASSERT(BufferLayout::GetComponents(element.GetType()) != 0, "Invalid element type (Components: 0)");
    ASSERT(GetGLType(element.GetType()) != GL_FALSE, "Invalid OpenGL element type");

    Bind();
    glVertexAttribPointer(
        index,
        BufferLayout::GetComponents(element.GetType()),
        GetGLType(element.GetType()),
        GL_FALSE,
        stride,
        (const void *)0);
}

void OpenGLVertexArray::EnableAttribute(unsigned int index, const BufferElement &element, int stride, int offset)
{
    // Should not be possible
    ASSERT(BufferLayout::GetComponents(element.GetType()) != 0, "Invalid element type (Components: 0)");
    ASSERT(GetGLType(element.GetType()) != GL_FALSE, "Invalid OpenGL element type");

    Bind();

    switch (element.GetType())
    {
    case BufferDataType::Int:
    case BufferDataType::UInt:
        glEnableVertexAttribArray(index);
        glVertexAttribIPointer(
            index,
            1,
            GL_UNSIGNED_INT,
            stride,
            (void *)(intptr_t)offset);
        break;
    default:
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            BufferLayout::GetComponents(element.GetType()),
            GetGLType(element.GetType()),
            GL_FALSE,
            stride,
            (void *)(intptr_t)offset);
        break;
    }
}

unsigned int OpenGLVertexArray::GetGLType(BufferDataType type) const
{
    switch (type)
    {
    case BufferDataType::Int:
        return GL_INT;
    case BufferDataType::Int2:
        return GL_INT;
    case BufferDataType::Int3:
        return GL_INT;
    case BufferDataType::Int4:
        return GL_INT;
    case BufferDataType::UInt:
        return GL_UNSIGNED_INT;
    case BufferDataType::Float:
        return GL_FLOAT;
    case BufferDataType::Float2:
        return GL_FLOAT;
    case BufferDataType::Float3:
        return GL_FLOAT;
    case BufferDataType::Float4:
        return GL_FLOAT;
    case BufferDataType::Double:
        return GL_DOUBLE;
    case BufferDataType::Bool:
        return GL_BOOL;
    case BufferDataType::Mat3:
        return GL_FLOAT;
    case BufferDataType::Mat4:
        return GL_FLOAT;
    };

    return GL_FALSE;
}
