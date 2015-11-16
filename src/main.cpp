#include <QApplication>
#include "App.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("Screenshotgun");
    QCoreApplication::setOrganizationDomain("screenshotgun.com");
    QCoreApplication::setApplicationName("Screenshotgun");

    QApplication app(argc, argv);

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    file.close();

    app.setQuitOnLastWindowClosed(false);
    app.setStyleSheet(style);

    App application;
    return app.exec();
}
