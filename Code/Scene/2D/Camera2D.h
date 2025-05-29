#pragma once

#include "Core/Math/Matrix.h"
#include "Scene/2D/Node2D.h"

class Camera2D : public Node2D
{
public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Render() override;

    Matrix4 GetProjectionMatrix();
    Matrix4 GetViewMatrix();

private:
    float m_Zoom = 1.0f;
};
