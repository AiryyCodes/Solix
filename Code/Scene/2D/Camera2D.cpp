#include "Scene/2D/Camera2D.h"
#include "Core/Math/Matrix.h"
#include "Core/Runtime.h"
#include "Renderer/IRenderer.h"

void Camera2D::Render()
{
    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();

    mainShader->SetUniform("u_View", GetViewMatrix());
    mainShader->SetUniform("u_Projection", GetProjectionMatrix());
}

Matrix4 Camera2D::GetProjectionMatrix()
{
    Runtime &runtime = Runtime::Get();

    float aspect = (float)runtime.GetWindow()->GetWidth() / (float)runtime.GetWindow()->GetHeight();
    float height = 2.0f;
    float width = height * aspect;

    float left = -width / 2.0f;
    float right = width / 2.0f;
    float top = height / 2.0f;
    float bottom = -height / 2.0f;

    return Matrix4::Orthographic(left, right, top, bottom, -1.0f, 1.0f);
}

Matrix4 Camera2D::GetViewMatrix()
{
    Matrix4 matrix = Matrix4::Identity();
    matrix.Translate(-GetPosition());
    return matrix;
}
