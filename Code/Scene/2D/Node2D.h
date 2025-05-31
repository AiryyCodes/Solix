#pragma once

#include "Core/Math/Matrix.h"
#include "Core/Math/Vector.h"
#include "Scene/Node.h"

class Node2D : public Node
{
    NODE_CLASS(Node2D, Node);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    /* FOR INTERNAL LOGIC */
    virtual void Init() override {}
    virtual void Update() override {}
    virtual void Render() override;

    Matrix4 GetTransformMatrix() const;

    const Vector2 &GetPosition() const { return m_Position; }
    void SetPosition(Vector2 position) { m_Position = position; }

private:
    Vector2 m_Position = {0.0f, 0.0f};
    Vector2 m_Scale = {1.0f, 1.0f};
    float m_Rotation = 0.0f;
};
