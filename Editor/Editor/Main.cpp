#include <cstdio>
#include <cstdlib>
#include <QGuiApplication>
#include <qguiapplication.h>

#include "Editor/Graphics/Window.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    EditorWindow window;
    window.Show();

    return app.exec();
}
