#include "Editor/Graphics/Window.h"

#include <QPainter>
#include <QGradient>
#include <string>

EditorWindow::EditorWindow(int width, int height, std::string title, QWindow *parent)
    : QWindow(parent), m_BackingStore(new QBackingStore(this))
{
    SetWidth(width);
    SetHeight(height);
    SetTitle(title);
}

void EditorWindow::OnRender()
{
    if (!isExposed())
        return;

    if (m_BackingStore->size() != size())
    {
        m_BackingStore->resize(size());
    }

    QRect rect(0, 0, width(), height());
    m_BackingStore->beginPaint(rect);

    QPaintDevice *device = m_BackingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), QColor(0.0f, 0.0f, 0.0f));
    // render(&painter);
    painter.end();

    m_BackingStore->endPaint();
    m_BackingStore->flush(rect);
}

void EditorWindow::exposeEvent(QExposeEvent *event)
{
    if (!isExposed())
        return;

    OnRender();
}

void EditorWindow::Show()
{
    QWindow::show();
}

int EditorWindow::GetWidth() const
{
    return width();
}

void EditorWindow::SetWidth(int width)
{
    setGeometry(0, 0, width, GetHeight());
}

int EditorWindow::GetHeight() const
{
    return height();
}

void EditorWindow::SetHeight(int height)
{
    setGeometry(0, 0, GetWidth(), height);
}

std::string EditorWindow::GetTitle() const
{
    return title().toStdString();
}
void EditorWindow::SetTitle(const std::string &title)
{
    setTitle(QString::fromStdString(title));
}
