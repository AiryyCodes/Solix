#include "Renderer/IRenderer.h"
#include <stdexcept>

static IRenderer *instance = nullptr;

IRenderer &IRenderer::Get()
{
    if (!instance)
    {
        throw std::runtime_error("No instance of IRenderer was found.");
    }
    return *instance;
}

void IRenderer::Set(IRenderer *renderer)
{
    instance = renderer;
}
