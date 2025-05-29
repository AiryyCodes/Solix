#include "Scene/2D/Node2D.h"
#include "Core/Math/Math.h"
#include "Core/Math/Matrix.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"

void Node2D::Render()
{
    Ref<IShader> mainShader = IRenderer::Get().GetMainShader();
    mainShader->SetUniform("u_Transform", GetTransformMatrix());
}

Matrix4 Node2D::GetTransformMatrix() const
{
    Matrix4 matrix = Matrix4::Identity();

    matrix.Translate(m_Position);

    matrix.RotateZ(Math::ToRadians(m_Rotation));

    matrix.Scale(m_Scale);

    return matrix;
}
