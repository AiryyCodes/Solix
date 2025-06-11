#pragma once

#include "Core/Math/Matrix.h"
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

    virtual void InspectorGUI() override;

    Matrix4 GetTransformMatrix() const;
    Matrix4 GetGlobalTransform() override;

    const Vector2 &GetPosition() const { return m_Position; }
    Vector2 &GetPosition() { return m_Position; }
    void SetPosition(const Vector2 &position);

    const Vector2 &GetScale() const { return m_Scale; }
    Vector2 &GetScale() { return m_Scale; }
    void SetScale(const Vector2 &scale);

    const float &GetRotation() const { return m_Rotation; }
    float &GetRotation() { return m_Rotation; }
    void SetRotation(float rotation);

private:
    Vector2 m_Position = {0.0f, 0.0f};
    Vector2 m_Scale = {1.0f, 1.0f};
    float m_Rotation = 0.0f;

    Matrix4 m_GlobalTransform;
};
