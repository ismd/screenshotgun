//#include <QtQml/QQmlEngine>
#include <QQmlContext>

#include "canvas.h"
#include "canvasprovider.h"

Canvas::Canvas(const QPixmap &pixmap) : screenshot(pixmap)
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QQuickView::SizeRootObjectToView);
    rootContext()->setContextProperty("object", this);
    engine()->addImageProvider(QLatin1String("canvas"), new CanvasProvider(pixmap));
    setSource(QUrl("qrc:/canvas.qml"));
}

Canvas::~Canvas()
{
}

QString Canvas::save()
{
    screenshot.save("/home/ismd/tmp.png");
    filename = "/home/ismd/tmp.png";

    return "/home/ismd/tmp.png";
}

void Canvas::upload()
{
    // Отправляем на сервер
    Server server;
    server.upload(filename);
    //exit(EXIT_SUCCESS);
}
