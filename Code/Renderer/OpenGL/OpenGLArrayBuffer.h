#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IArrayBuffer.h"

class OpenGLArrayBuffer : public IArrayBuffer
{
public:
    ~OpenGLArrayBuffer();

    virtual Optional<Error> OnInit(const void *data, int size) override;

    virtual void Bind() override;
    virtual void Unbind() override;

private:
    unsigned int m_Id = 0;
};
