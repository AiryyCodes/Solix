#pragma once

#include "Core/Graphics/IWindow.h"

#include <QWindow>
#include <QScopedPointer>
#include <QBackingStore>
#include <string>

class EditorWindow : public QWindow, public IWindow
{
public:
    explicit EditorWindow(int width = 1280, int height = 720, std::string title = "Solix Engine", QWindow *parent = nullptr);

    void OnRender() override;

    void Show() override;

    int GetWidth() const override;
    void SetWidth(int width) override;

    int GetHeight() const override;
    void SetHeight(int height) override;

    std::string GetTitle() const override;
    void SetTitle(const std::string &title) override;

private:
    void exposeEvent(QExposeEvent *event) override;

private:
    QScopedPointer<QBackingStore> m_BackingStore;
};
