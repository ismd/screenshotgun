#include "editorview.h"
#include "const.h"
#include "updater.h"
#include <QDebug>
#include <QApplication>

void msgHandler(QtMsgType type, const char* msg)
{
    const char symbols[] = {'I', 'E', '!', 'X'};
    QString output = QString("[%1] %2").arg(symbols[type]).arg(msg);
    std::cerr << output.toStdString() << std::endl;

    if (type == QtFatalMsg) {
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMsgHandler(msgHandler);
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

    if (args.contains("--update-remove")) {
        int pathIndex = args.indexOf("--update-remove") + 1;

        if (pathIndex >= args.size()) {
            qCritical() << "Bad update-remove file path";
            exit(1);
        }

        QFile fileForRemove(args.at(pathIndex));
        fileForRemove.remove();
    }

    if (args.contains("--version") || args.contains("-v")) {
        qDebug() << VERSION;
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
