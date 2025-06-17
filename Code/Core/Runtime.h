#pragma once

#include "Core/Base.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IWindow.h"
#include "Scene/Scene.h"

#include <memory>

class Runtime
{
public:
    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnShutdown() = 0;

    void Init();
    void Update();
    void Shutdown();

    Ref<IWindow> GetWindow() const { return m_Window; }
    Ref<IRenderer> GetRenderer() const { return m_Renderer; }

    Ref<Scene> GetScene() const { return m_Scene; }

    template <typename T>
    T *As()
    {
        return static_cast<T *>(m_Instance);
    }

    static Runtime &Get() { return *m_Instance; }

private:
    static Runtime *m_Instance;

    Ref<IWindow> m_Window;
    Ref<IRenderer> m_Renderer;

    Ref<Scene> m_Scene;
};

Ref<Runtime> StartRuntime();
