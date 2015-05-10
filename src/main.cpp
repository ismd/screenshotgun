#include <iostream>
#include <QApplication>
#include "const.h"
#include "editorview.h"
#include "updater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.contains("--update")) {
        int pathIndex = args.indexOf("--update") + 1;

        if (pathIndex >= args.size()) {
            std::cerr << "Bad update file path" << std::endl;
            exit(1);
        }

        Updater updater;
        updater.copyNew(args.at(pathIndex));
        return 0;
    }

    if (args.contains("--update-remove")) {
        int pathIndex = args.indexOf("--update-remove") + 1;

        if (pathIndex >= args.size()) {
            std::cerr << "Bad update-remove file path" << std::endl;
            exit(1);
        }

        QFile fileForRemove(args.at(pathIndex));
        fileForRemove.remove();
    }

    if (args.contains("--version") || args.contains("-v")) {
        std::cout << VERSION << std::endl;
        return 0;
    }

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    file.close();

    app.setQuitOnLastWindowClosed(false);
    app.setStyleSheet(style);

    EditorView window;
    return app.exec();
}
