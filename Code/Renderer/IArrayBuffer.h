#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"

class IArrayBuffer
{
public:
    virtual ~IArrayBuffer() = default;

    virtual Optional<Error> OnInit(const void *data, int size) = 0;
};
