#pragma once

#include "Core/Base.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

class OpenGLRenderer : public IRenderer
{
public:
    OpenGLRenderer();

    virtual Optional<Error> OnPreInit() override;
    virtual Optional<Error> OnInit() override;

    virtual void OnShutdown() override;

    virtual void Clear() const override;
    virtual void ClearColor(const Color &color) const override;
    virtual void SetViewport(int width, int height, int x, int y) const override;

    virtual void DrawArrays(const Mesh &mesh) const override;

    virtual Ref<IArrayBuffer> CreateArrayBuffer() override;
    virtual Ref<IVertexArray> CreateVertexArray() override;
    virtual Ref<IShader> CreateShader() override;

    virtual Ref<IShader> GetMainShader() override { return m_MainShader; }

private:
    Ref<IShader> m_MainShader;
};
