#pragma once

#include "Core/Base.h"
#include "Renderer/IRenderer.h"
#include "Renderer/IWindow.h"

class Application
{
public:
    static Ref<Application> Start();
    static Application &Get() { return *m_Instance; }

    void OnInit();
    void OnShutdown();

    Ref<IRenderer> GetRenderer() const { return m_Renderer; }
    Ref<IWindow> GetWindow() const { return m_Window; }

private:
    Ref<IRenderer> m_Renderer;
    Ref<IWindow> m_Window;

    static Ref<Application> m_Instance;
};
