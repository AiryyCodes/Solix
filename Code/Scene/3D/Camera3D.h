#pragma once

#include "Scene/3D/Node3D.h"

class Camera3D : public Node3D
{
    NODE_CLASS(Camera3D, Node3D);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Render() override;

    Matrix4 GetProjectionMatrix();
    Matrix4 GetViewMatrix();

private:
    float m_Fov = 45.0f;

    float m_Near = 0.01f;
    float m_Far = 100.0f;
};
