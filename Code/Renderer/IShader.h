#pragma once

#include "Core/Math/Matrix.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <string>

class IShader
{
public:
    virtual ~IShader() = default;

    virtual Optional<Error> OnInit(const std::string &vertexPath, const std::string &fragmentPath) = 0;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetUniform(const std::string &name, const Matrix4 &value) = 0;
};
