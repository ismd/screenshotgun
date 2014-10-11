#include <QApplication>

#include "editorview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    EditorView *window = new EditorView;
    window->showFullScreen();

    return app.exec();
}
