#pragma once

#include "Core/Math/Matrix.h"
#include "Scene/2D/Node2D.h"

class Camera2D : public Node2D
{
public:
    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}

    Matrix4 GetProjectionMatrix();
    Matrix4 GetViewMatrix();

private:
    float m_Zoom = 1.0f;
};
