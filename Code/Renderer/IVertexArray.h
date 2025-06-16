#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/Layout.h"

class IVertexArray
{
public:
    virtual ~IVertexArray() = default;

    virtual Optional<Error> OnInit() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetLayout(const BufferLayout &layout) = 0;
    virtual void EnableAttribute(unsigned int index, const BufferElement &element, int stride) = 0;
    virtual void EnableAttribute(unsigned int index, const BufferElement &element, int stride, int offset) = 0;
};
