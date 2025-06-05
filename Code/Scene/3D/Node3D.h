#pragma once

#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Scene/Node.h"

class Node3D : public Node
{
    NODE_CLASS(Node3D, Node);

public:
    virtual void OnInit() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}

    /* FOR INTERNAL LOGIC */
    virtual void Init() override {}
    virtual void Update() override {}
    virtual void Render() override;

    Matrix4 GetTransformMatrix() const;

    Vector3 GetUp() const;
    Vector3 GetFront() const;
    Vector3 GetRight() const;

    const Vector3 &GetPosition() const { return m_Position; }
    Vector3 &GetPosition() { return m_Position; }
    void SetPosition(const Vector3 position) { m_Position = position; }

    const Vector3 &GetScale() const { return m_Scale; }
    Vector3 &GetScale() { return m_Scale; }
    void SetScale(const Vector3 &scale) { m_Scale = scale; }

    const Vector3 &GetRotation() const { return m_Rotation; }
    Vector3 &GetRotation() { return m_Rotation; }
    void SetRotation(Vector3 rotation) { m_Rotation = rotation; }

private:
    Vector3 m_Position = {0.0f, 0.0f, 0.0f};
    Vector3 m_Scale = {1.0f, 1.0f, 1.0f};
    Vector3 m_Rotation = {0.0f, 0.0f, 0.0f};
};
