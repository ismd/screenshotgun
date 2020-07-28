#include "App.h"
#include "System.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    System system;
    if (system.isLaunched()) {
        qDebug() << "The application is already running";
        return 1;
    }

    app.setOrganizationName("Screenshotgun");
    app.setOrganizationDomain("screenshotgun.com");
    app.setApplicationName("Screenshotgun");

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    file.close();

    app.setQuitOnLastWindowClosed(false);
    app.setStyleSheet(style);

    App application;
    return app.exec();
}
