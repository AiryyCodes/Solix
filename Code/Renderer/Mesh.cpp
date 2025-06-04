#include "Renderer/Mesh.h"
#include "Renderer/IRenderer.h"
#include "Renderer/Layout.h"

Mesh::Mesh()
{
    IRenderer &renderer = IRenderer::Get();

    m_VertexArray = renderer.CreateVertexArray();
    m_VertexArray->OnInit();
}

void Mesh::Bind() const
{
    m_VertexArray->Bind();
}

void Mesh::Unbind() const
{
    m_VertexArray->Unbind();
}

void Mesh::SetVertices(List<Vector3> vertices)
{
    IRenderer &renderer = IRenderer::Get();

    m_VertexArray->Bind();

    auto buffer = renderer.CreateArrayBuffer();
    buffer->OnInit(vertices.GetData(), vertices.GetSize());

    m_ArrayBuffers.Add(buffer);

    m_NumVertices += vertices.GetLength();
}

void Mesh::SetLayout(const BufferLayout &layout)
{
    Bind();
    m_ArrayBuffers.Get(0)->Bind();

    m_VertexArray->SetLayout(layout);
}
