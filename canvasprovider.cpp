#include "canvasprovider.h"

CanvasProvider::CanvasProvider(const QPixmap &pixmap) : QQuickImageProvider(QQuickImageProvider::Pixmap), pixmap(pixmap)
{
}

QPixmap CanvasProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    return pixmap;
}
