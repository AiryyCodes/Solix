#include "Renderer/OpenGL/OpenGLShader.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <glad/gl.h>

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_Id);
}

Optional<Error> OpenGLShader::OnInit(const std::string &vertexPath, const std::string &fragmentPath)
{
    Result<unsigned int, Error> vertexResult = CompileShader(vertexPath, "vertex", GL_VERTEX_SHADER);
    if (vertexResult.IsError())
    {
        LOG_ERROR(vertexResult.GetError().GetMessage());
        return Optional<Error>(Error("Failed to create vertex shader."));
    }

    Result<unsigned int, Error> fragmentResult = CompileShader(fragmentPath, "fragment", GL_FRAGMENT_SHADER);
    if (fragmentResult.IsError())
    {
        LOG_ERROR(fragmentResult.GetError().GetMessage());
        return Optional<Error>(Error("Failed to create fragment shader."));
    }

    unsigned int vertexId = vertexResult.GetValue();
    unsigned int fragmentId = fragmentResult.GetValue();

    m_Id = glCreateProgram();

    glAttachShader(m_Id, vertexId);
    glAttachShader(m_Id, fragmentId);

    glLinkProgram(m_Id);

    int status;

    glGetProgramiv(m_Id, GL_LINK_STATUS, &status);

    if (!status)
    {
        char log[1024];
        glGetProgramInfoLog(m_Id, 1024, NULL, log);

        return Optional<Error>(Error("Failed to compile shader program."));
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return Optional<Error>::Empty();
}

Result<unsigned int, Error> OpenGLShader::CompileShader(const std::string &path, const std::string &name, unsigned int type)
{
    unsigned int id = glCreateShader(type);

    File file(path);
    std::string source = file.ReadAll();
    if (source.empty())
    {
        return Result<unsigned int, Error>::Error("Failed to read shader file '" + path + "'");
    }

    const char *cSource = source.c_str();
    glShaderSource(id, 1, &cSource, NULL);

    glCompileShader(id);

    int status;

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        char log[1024];
        glGetShaderInfoLog(id, 1024, NULL, log);

        return Result<unsigned int, Error>::Error("Failed to compile " + name + " shader.\n" + log);
    }

    return Result<unsigned int, Error>::Ok(id);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_Id);
}

void OpenGLShader::Unbind() const
{
    if (glIsProgram(m_Id))
    {
        glUseProgram(0);
    }
}

void OpenGLShader::SetUniform(const std::string &name, const Matrix4 &value)
{
    int location = glGetUniformLocation(m_Id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, value.GetValue());
}

void OpenGLShader::SetUniform(const std::string &name, bool value)
{
    int location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1i(location, value);
}

void OpenGLShader::SetUniform(const std::string &name, int value)
{
    int location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1i(location, value);
}
