#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IRenderer.h"

class OpenGLRenderer : public IRenderer
{
public:
    virtual Optional<Error> OnPreInit() override;
    virtual Optional<Error> OnInit() override;

    virtual void Clear() const override;
    virtual void ClearColor(const Color &color) const override;
};
