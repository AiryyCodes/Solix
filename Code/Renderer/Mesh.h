#pragma once

#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Math/Vector.h"
#include "Renderer/IArrayBuffer.h"
#include "Renderer/IVertexArray.h"

class Mesh
{
public:
    Mesh();

    void Bind() const;
    void Unbind() const;

    void SetVertices(List<Vector3> vertices);

    int GetNumVertices() const { return m_NumVertices; }

private:
    List<Ref<IArrayBuffer>> m_ArrayBuffers;
    Ref<IVertexArray> m_VertexArray;

    int m_NumVertices;
};
