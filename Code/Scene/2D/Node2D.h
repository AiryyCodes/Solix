#pragma once

#include "Core/Math/Matrix.h"
#include "Core/Math/Vector.h"
#include "Scene/Node.h"

class Node2D : public Node
{
public:
    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnRender() {}

    Matrix4 GetTransformMatrix() const;

    const Vector2 &GetPosition() const { return m_Position; }
    void SetPosition(Vector2 position) { m_Position = position; }

private:
    Vector2 m_Position = {0.0f, 0.0f};
    float m_Rotation = 0.0f;
    Vector2 m_Scale = {1.0f, 1.0f};
};
