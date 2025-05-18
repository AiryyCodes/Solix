#include "Renderer/OpenGL/OpenGLVertexArray.h"
#include "Core/Optional.h"
#include "Core/Result.h"

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
