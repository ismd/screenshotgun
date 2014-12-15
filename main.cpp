#include <QApplication>
#include "editorview.h"
#include "const.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Check for a new version
    QString dir = app.applicationDirPath();

    #ifdef Q_OS_WIN32
    QFile file(dir + "/open-screen-cloud-new.exe");
    #endif
    #ifndef Q_OS_WIN32
    QFile file(dir + "/open-screen-cloud-new");
    #endif

    QString filename = QFileInfo(app.applicationFilePath()).fileName();

    #ifdef Q_OS_WIN32
    if ("open-screen-cloud-new.exe" == filename) {
    #endif
    #ifndef Q_OS_WIN32
    if ("open-screen-cloud-new" == filename) {
    #endif
        #ifdef Q_OS_WIN32
        QString origFilename = dir + "/open-screen-cloud.exe";
        #endif
        #ifndef Q_OS_WIN32
        QString origFilename = dir + "/open-screen-cloud";
        #endif

        QFile origFile(origFilename);
        origFile.remove();

        if (!file.copy(origFilename)) {
            exit(1);
        }

        QProcess::startDetached(origFilename);
        exit(12);
    } else if (file.exists()) {
        file.remove();
    }

    EditorView window;
    return app.exec();
}
