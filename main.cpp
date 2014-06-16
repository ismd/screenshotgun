//#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QPixmap>

#include "canvas.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Делаем скриншот
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId());

    // Отображаем canvas
    Canvas viewer(screenshot);
    viewer.showFullScreen();

    return app.exec();
}
