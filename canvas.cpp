//#include <QtQml/QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "canvas.h"
#include "canvasprovider.h"

Canvas::Canvas(const QPixmap &pixmap) : screenshot(pixmap)
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QQuickView::SizeRootObjectToView);

    qmlRegisterType<Server>("ru.sibirix.osc", 1, 0, "Server");
    engine()->addImageProvider(QLatin1String("canvas"), new CanvasProvider(pixmap));

    setSource(QUrl("qrc:/canvas.qml"));

    // Saving image
    QFile file("/home/ismd/Загрузки/tmp.png");
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
    file.close();
}

Canvas::~Canvas()
{
}
