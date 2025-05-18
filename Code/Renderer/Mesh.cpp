#include "Renderer/Mesh.h"
#include "Core/Application.h"
#include "Renderer/IRenderer.h"

Mesh::Mesh()
{
    Ref<IRenderer> renderer = Application::Get().GetRenderer();

    m_VertexArray = renderer->CreateVertexArray();
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
    Ref<IRenderer> renderer = Application::Get().GetRenderer();

    m_VertexArray->Bind();

    auto buffer = renderer->CreateArrayBuffer();
    buffer->OnInit(vertices.GetData(), vertices.GetSize());

    m_ArrayBuffers.Add(buffer);

    m_NumVertices = vertices.GetLength();
}
