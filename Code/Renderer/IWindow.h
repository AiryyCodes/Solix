#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual Optional<Error> OnInit() = 0;

    virtual void PollEvents() const = 0;
    virtual void SwapBuffers() const = 0;

    virtual bool IsClosing() const = 0;
};
