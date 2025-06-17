#pragma once

#include "Core/Base.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IShader.h"
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
    virtual void InspectorGUI() override;

    Matrix4 GetTransformMatrix() const;
    Matrix4 GetGlobalTransform() override;

    Vector3 GetUp();
    Vector3 GetGlobalUp();

    Vector3 GetFront();
    Vector3 GetGlobalFront();

    Vector3 GetRight();
    Vector3 GetGlobalRight();

    const Vector3 &GetPosition() const { return m_Position; }
    Vector3 &GetPosition() { return m_Position; }
    Vector3 GetGlobalPosition();

    void SetPosition(const Vector3 &position);

    const Vector3 &GetScale() const { return m_Scale; }
    Vector3 &GetScale() { return m_Scale; }
    Vector3 GetGlobalScale();

    void SetScale(const Vector3 &scale);

    const Vector3 &GetRotation() const { return m_Rotation; }
    Vector3 &GetRotation() { return m_Rotation; }
    Vector3 GetGlobalRotation();

    void SetRotation(const Vector3 &rotation);

    Ref<IShader> GetShader() const { return m_Shader; }
    void SetShader(Ref<IShader> shader) { m_Shader = shader; }

private:
    Matrix3 GetRotationMatrix(const Matrix4 &matrix);

private:
    Vector3 m_Position = {0.0f, 0.0f, 0.0f};
    Vector3 m_Scale = {1.0f, 1.0f, 1.0f};
    Vector3 m_Rotation = {0.0f, 0.0f, 0.0f};

    Matrix4 m_GlobalTransform;

    Ref<IShader> m_Shader = IRenderer::Get().GetMainShader();
};
