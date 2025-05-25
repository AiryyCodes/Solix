#pragma once

#include "Core/Base.h"
#include "Core/Color.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IArrayBuffer.h"
#include "Renderer/IShader.h"
#include "Renderer/IVertexArray.h"
#include "Renderer/Mesh.h"

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual Optional<Error> OnPreInit() = 0;
    virtual Optional<Error> OnInit() = 0;

    virtual void Clear() const = 0;
    virtual void ClearColor(const Color &color) const = 0;
    virtual void SetViewport(int width, int height, int x, int y) const = 0;

    virtual void DrawArrays(const Mesh &mesh) const = 0;

    virtual Ref<IArrayBuffer> CreateArrayBuffer() = 0;
    virtual Ref<IVertexArray> CreateVertexArray() = 0;
    virtual Ref<IShader> CreateShader() = 0;
};
