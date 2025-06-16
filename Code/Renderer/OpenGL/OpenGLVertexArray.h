#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IVertexArray.h"
#include "Renderer/Layout.h"

class OpenGLVertexArray : public IVertexArray
{
public:
    ~OpenGLVertexArray();

    virtual Optional<Error> OnInit() override;

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void SetLayout(const BufferLayout &layout) override;
    virtual void EnableAttribute(unsigned int index, const BufferElement &element, int stride) override;
    virtual void EnableAttribute(unsigned int index, const BufferElement &element, int stride, int offset) override;

private:
    unsigned int GetGLType(BufferDataType type) const;

private:
    unsigned int m_Id = 0;

    BufferLayout m_Layout;
};
