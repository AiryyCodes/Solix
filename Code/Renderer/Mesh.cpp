#include "Renderer/Mesh.h"
#include "Core/Logger.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IArrayBuffer.h"
#include "Renderer/IRenderer.h"
#include "Renderer/Layout.h"

#include <glad/gl.h>

Mesh::Mesh()
{
    IRenderer &renderer = IRenderer::Get();

    m_VertexArray = renderer.CreateVertexArray();
    m_VertexArray->OnInit();
}

void Mesh::Init()
{
    // TODO: Maybe make this optional
    GenerateNormals();

    List<Vertex> vertices;
    for (int i = 0; i < m_NumVertices; i++)
    {
        Vertex vertex;
        vertex.position = m_Vertices.Get(i);
        vertex.normal = m_Normals.Get(i);

        vertices.Add(vertex);
    }

    IRenderer &renderer = IRenderer::Get();

    m_VertexArray->Bind();

    Ref<IArrayBuffer> buffer = renderer.CreateArrayBuffer();
    buffer->OnInit(vertices.GetData(), vertices.GetSize());
    buffer->Bind();

    BufferElement positionElement("a_Position", BufferDataType::Float3);
    BufferElement normalElement("a_Normal", BufferDataType::Float3);

    m_VertexArray->EnableAttribute(0, positionElement, sizeof(Vertex), offsetof(Vertex, position));
    m_VertexArray->EnableAttribute(1, normalElement, sizeof(Vertex), offsetof(Vertex, normal));

    m_ArrayBuffers.Add(buffer);
}

void Mesh::Bind() const
{
    if (m_Material.GetTexture())
    {
        IRenderer::Get().ActivateTexture(0);
        m_Material.GetTexture()->Bind();
    }
    m_VertexArray->Bind();
}

void Mesh::Unbind() const
{
    m_VertexArray->Unbind();
}

void Mesh::GenerateNormals()
{
    if (m_NumVertices % 3 != 0)
    {
        LOG_WARNING("Number of vertices is not a multiple of 3 (got {})", m_NumVertices);
        return;
    }

    m_Normals.Clear();

    for (int i = 0; i < m_NumVertices; i += 3)
    {
        Vector3 &v0 = m_Vertices.Get(i);
        Vector3 &v1 = m_Vertices.Get(i + 1);
        Vector3 &v2 = m_Vertices.Get(i + 2);

        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;
        Vector3 normal = edge1.Cross(edge2).Normalized();

        m_Normals.Add(normal);
        m_Normals.Add(normal);
        m_Normals.Add(normal);
    }
}

void Mesh::SetVertices(List<Vector3> vertices)
{
    IRenderer &renderer = IRenderer::Get();

    m_Vertices = vertices;
    m_NumVertices = vertices.GetLength();
}

void Mesh::SetLayout(const BufferLayout &layout)
{
    if (m_ArrayBuffers.GetLength() != layout.GetElements().GetLength())
    {
        LOG_ERROR("Array buffer length must be equal to layout.");
        return;
    }

    m_VertexArray->Bind();

    for (int i = 0; i < m_ArrayBuffers.GetLength(); i++)
    {
        if (i >= m_ArrayBuffers.GetLength())
        {
            LOG_ERROR("Missing array buffer for attribute index {}", i);
            continue;
        }

        const BufferElement &element = layout.GetElements().Get(i);

        m_ArrayBuffers.Get(i)->Bind();

        GLint bufferBinding = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferBinding);
        LOG_INFO("Currently bound GL_ARRAY_BUFFER: {}", bufferBinding);

        m_VertexArray->EnableAttribute(i, element, 0);
    }
}
