#pragma once

#include "Core/Base.h"
#include "Core/Runtime.h"
#include "UI/GUI.h"

class EditorRuntime : public Runtime
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnShutdown() override;

private:
    Ref<GUI> m_GUI;
};
