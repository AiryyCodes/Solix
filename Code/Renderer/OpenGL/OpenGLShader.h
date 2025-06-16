#pragma once

#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IShader.h"

#include <string>

class OpenGLShader : public IShader
{
public:
    ~OpenGLShader();

    virtual Optional<Error> OnInit(const std::string &vertexPath, const std::string &fragmentPath) override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetUniform(const std::string &name, const Matrix4 &value) override;

private:
    Result<unsigned int, Error> CompileShader(const std::string &path, const std::string &name, unsigned int type);

private:
    unsigned int m_Id = 0;
};
