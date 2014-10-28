#include <QApplication>
#include "editorview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initializing settings
    //QSettings settings("openscreencloud");
    //settings.setValue("test", "value");

    EditorView *window = new EditorView;
    //window->showFullScreen();

    return app.exec();
}
