#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IVertexArray.h"

class OpenGLVertexArray : public IVertexArray
{
public:
    ~OpenGLVertexArray();

    virtual Optional<Error> OnInit() override;

    virtual void Bind() override;
    virtual void Unbind() override;

private:
    unsigned int m_Id = 0;
};
