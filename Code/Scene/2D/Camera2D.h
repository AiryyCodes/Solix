#pragma once

#include "Core/Math/Matrix.h"
#include "Core/Object.h"
#include "Scene/2D/Node2D.h"
#include "Scene/Node.h"

class Camera2D : public Node2D
{
    NODE_CLASS(Camera2D, Node2D);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    virtual void Render() override;

    virtual void OnRegisterProperties() override
    {
        REGISTER_PROPERTY(Camera2D, "Zoom", GetZoom, SetZoom);
    }

    Matrix4 GetProjectionMatrix();
    Matrix4 GetViewMatrix();

    float GetZoom() const { return m_Zoom; }
    void SetZoom(float zoom) { m_Zoom = zoom; }

private:
    float m_Zoom = 1.0f;
};
