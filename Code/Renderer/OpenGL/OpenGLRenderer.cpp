#include "Renderer/OpenGL/OpenGLRenderer.h"
#include "Core/Color.h"
#include "Core/Logger.h"
#include "Core/Optional.h"
#include "Core/Result.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

Optional<Error> OpenGLRenderer::OnPreInit()
{
    LOG_INFO("Initializing GLFW...");

    if (!glfwInit())
    {
        return Optional<Error>(Error("Failed to initialize GLFW."));
    }

    LOG_INFO("Successfully initialized GLFW!");

    return Optional<Error>::Empty();
}

Optional<Error> OpenGLRenderer::OnInit()
{
    LOG_INFO("Loading OpenGL context...");

    int status = gladLoadGL(glfwGetProcAddress);
    if (!status)
    {
        return Optional<Error>(Error("Failed to initialize the OpenGL context"));
    }

    LOG_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(status), GLAD_VERSION_MINOR(status));

    return Optional<Error>::Empty();
}

void OpenGLRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::ClearColor(const Color &color) const
{
    Color normalized = color.Normalize();
    glClearColor(normalized.r, normalized.g, normalized.b, normalized.a);
}
