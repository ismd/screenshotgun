#include "editorview.h"
#include "const.h"
#include "updater.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.contains("--update")) {
        int pathIndex = args.indexOf("--update") + 1;

        if (pathIndex >= args.size()) {
            qCritical() << "Bad update file path";
            exit(1);
        }

        Updater updater;
        updater.copyNew(args.at(pathIndex));
        return 0;
    }

    if (args.contains("--version") || args.contains("-v")) {
        qDebug() << VERSION;
        return 0;
    }

    EditorView window;
    return app.exec();
}
