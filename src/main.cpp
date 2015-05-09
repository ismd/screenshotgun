#include "editorview.h"
#include "const.h"
#include "updater.h"
#include <QDebug>
#include <QApplication>
#include <iostream>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
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
