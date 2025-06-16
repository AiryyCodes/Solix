#include "Renderer/OpenGL/OpenGLRenderer.h"
#include "Core/Color.h"
#include "Core/Logger.h"
#include "Core/Optional.h"
#include "Core/Result.h"
#include "Renderer/IShader.h"
#include "Renderer/OpenGL/OpenGLArrayBuffer.h"
#include "Renderer/OpenGL/OpenGLShader.h"
#include "Renderer/OpenGL/OpenGLTexture.h"
#include "Renderer/OpenGL/OpenGLVertexArray.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

void APIENTRY DebugMessageCallback(GLenum source,
                                   GLenum type,
                                   unsigned int id,
                                   GLenum severity,
                                   GLsizei length,
                                   const char *message,
                                   const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

OpenGLRenderer::OpenGLRenderer()
{
    IRenderer::Set(this);
}

Optional<Error> OpenGLRenderer::OnPreInit()
{
    LOG_INFO("Initializing GLFW...");

    if (!glfwInit())
    {
        return Optional<Error>(Error("Failed to initialize GLFW."));
    }

    LOG_INFO("Successfully initialized GLFW!");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

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

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glEnable(GL_DEPTH_TEST);

    ImGui_ImplOpenGL3_Init();

    Ref<IShader> shader = CreateShader();
    auto result = shader->OnInit("Resources/Shaders/Main.vert", "Resources/Shaders/Main.frag");
    if (result.HasValue())
    {
        LOG_ERROR(result.GetValue());
        return Optional<Error>(Error("Failed to initialize main shader."));
    }

    m_MainShader = shader;

    return Optional<Error>::Empty();
}

void OpenGLRenderer::OnFrameBegin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void OpenGLRenderer::OnFrameEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OpenGLRenderer::OnShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_MainShader.reset();
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

void OpenGLRenderer::SetViewport(int width, int height, int x, int y) const
{
    glViewport(x, y, width, height);
}

void OpenGLRenderer::DrawArrays(const Mesh &mesh) const
{
    mesh.Bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.GetNumVertices());
}

void OpenGLRenderer::ActivateTexture(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
}

Ref<IArrayBuffer> OpenGLRenderer::CreateArrayBuffer()
{
    return CreateRef<OpenGLArrayBuffer>();
}

Ref<IVertexArray> OpenGLRenderer::CreateVertexArray()
{
    return CreateRef<OpenGLVertexArray>();
}

Ref<IShader> OpenGLRenderer::CreateShader()
{
    return CreateRef<OpenGLShader>();
}

Ref<Texture> OpenGLRenderer::CreateTexture(const std::string &path)
{
    return CreateRef<OpenGLTexture>(path);
}
