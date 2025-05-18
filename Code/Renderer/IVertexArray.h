#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"

class IVertexArray
{
public:
    virtual ~IVertexArray() = default;

    virtual Optional<Error> OnInit() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
};
