//#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QPixmap>

#include "canvas.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Making screenshot
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId());

    // Showing canvas
    Canvas viewer(screenshot);
    viewer.showFullScreen();

    return app.exec();
}
