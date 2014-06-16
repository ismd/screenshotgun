#ifndef CANVASPROVIDER_H
#define CANVASPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QPixmap>

class CanvasProvider : public QQuickImageProvider
{

public:
    CanvasProvider(const QPixmap &pixmap);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    const QPixmap &pixmap;
};

#endif // CANVASPROVIDER_H
