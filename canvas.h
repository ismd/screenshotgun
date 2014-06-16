#ifndef CANVAS_H
#define CANVAS_H

#include <QtQuick/QQuickView>
#include <QPixmap>

#include "server.h"

class Canvas : public QQuickView
{
    Q_OBJECT

public:
    explicit Canvas(const QPixmap &pixmap);
    virtual ~Canvas();

private:
    const QPixmap &screenshot;
    QString filename;
};

#endif // CANVAS_H
