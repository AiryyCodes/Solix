#include "Scene/3D/Camera3D.h"
#include "Core/Base.h"
#include "Core/Math/Vector3.h"
#include "Core/Runtime.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

void Camera3D::Render()
{
    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();

    mainShader->SetUniform("u_View", GetViewMatrix());
    mainShader->SetUniform("u_Projection", GetProjectionMatrix());
}

Matrix4 Camera3D::GetProjectionMatrix()
{
    Runtime &runtime = Runtime::Get();

    float aspect = (float)runtime.GetWindow()->GetWidth() / (float)runtime.GetWindow()->GetHeight();

    return Matrix4::Perspective(m_Fov, aspect, m_Near, m_Far);
}

Matrix4 Camera3D::GetViewMatrix()
{
    return Matrix4::LookAt(GetPosition(), GetPosition() + GetFront(), GetUp());
}
