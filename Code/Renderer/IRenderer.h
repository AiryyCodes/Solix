#pragma once

#include "Core/Color.h"
#include "Core/Optional.h"
#include "Core/Result.h"

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual Optional<Error> OnPreInit() = 0;
    virtual Optional<Error> OnInit() = 0;

    virtual void Clear() const = 0;
    virtual void ClearColor(const Color &color) const = 0;
};
