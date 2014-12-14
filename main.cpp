#include <QApplication>
#include "editorview.h"
#include "const.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Check for a new version
    QString dir = app.applicationDirPath();
    QFile file(dir + "/open-screen-cloud-new");

    if ("open-screen-cloud-new" == app.applicationName()) {
        QString origFilename = dir + "/open-screen-cloud";

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
