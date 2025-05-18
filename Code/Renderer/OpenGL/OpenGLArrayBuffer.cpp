#include "Renderer/OpenGL/OpenGLArrayBuffer.h"
#include "Core/Math/Vector.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <glad/gl.h>

OpenGLArrayBuffer::~OpenGLArrayBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

Optional<Error> OpenGLArrayBuffer::OnInit(const void *data, int size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return Optional<Error>::Empty();
}
