#pragma once

#include <string>

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void OnRender() = 0;

    virtual void Show() = 0;

    virtual int GetWidth() const = 0;
    virtual void SetWidth(int width) = 0;

    virtual int GetHeight() const = 0;
    virtual void SetHeight(int height) = 0;

    virtual std::string GetTitle() const = 0;
    virtual void SetTitle(const std::string &title) = 0;
};
