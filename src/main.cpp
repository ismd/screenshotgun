#include <QApplication>
#include "editorview.h"
#include "const.h"
#include "updater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.contains("--update")) {
        Updater updater;
        updater.copyNew(args.at(args.indexOf("--update") + 1));
        return 0;
    }

    if (args.contains("--version") || args.contains("-v")) {
        qDebug() << VERSION;
        return 0;
    }

    EditorView window;
    return app.exec();
}
