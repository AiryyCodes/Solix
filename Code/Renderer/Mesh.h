#pragma once

#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IArrayBuffer.h"
#include "Renderer/IVertexArray.h"
#include "Renderer/Layout.h"
#include "Renderer/Material.h"

struct Vertex
{
    Vector3 position;
    Vector3 normal;
};

class Mesh
{
public:
    Mesh();

    void Init();

    void Bind() const;
    void Unbind() const;

    void GenerateNormals();

    void SetLayout(const BufferLayout &layout);

    void AddArrayBuffer(Ref<IArrayBuffer> buffer);

    void SetVertices(List<Vector3> vertices);

    Material &GetMaterial() { return m_Material; }
    const Material &GetMaterial() const { return m_Material; }
    void SetMaterial(const Material &material) { m_Material = material; }

    int GetNumVertices() const { return m_NumVertices; }

private:
    List<Ref<IArrayBuffer>> m_ArrayBuffers;
    Ref<IVertexArray> m_VertexArray;

    Material m_Material;

    List<Vector3> m_Vertices;
    List<Vector3> m_Normals;
    int m_NumVertices = 0;
};
