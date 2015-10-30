#include <QtCore/qmath.h>
#include "ArrowMode.h"

ArrowMode::ArrowMode(QGraphicsScene& scene) : AbstractMode(scene) {
}

void ArrowMode::init(int x, int y) {
    line = new QGraphicsLineItem(x, y, x, y);
    line->setPen(pen);

    path = new QGraphicsPathItem();
    QPen pathPen = QPen(pen);
    pathPen.setWidth(1);

    path->setPen(pathPen);
    path->setBrush(QBrush(pen.brush()));

    scene_.addItem(line);
    scene_.addItem(path);
}

void ArrowMode::move(int x, int y) {
    QLineF l = line->line();
    l.setP2(QPointF(x, y));

    // Angle
    qreal angle = qAtan(l.dy() / l.dx());
    int length = 30;

    // Triangle
    QPainterPath painterPath;

    int sign = l.dx() < 0 ? 1 : -1;

    painterPath.moveTo(x, y);
    painterPath.lineTo(x + qCos(angle - .2) * length * sign,
                       y + qSin(angle - .2) * length * sign);
    painterPath.lineTo(x + qCos(angle + .2) * length * sign,
                       y + qSin(angle + .2) * length * sign);
    painterPath.lineTo(x, y);

    l.setP2(QPointF(x + qCos(angle) * 5 * sign,
                    y + qSin(angle) * 5 * sign));

    line->setLine(l);
    path->setPath(painterPath);
}

void ArrowMode::stop(int x, int y) {
    move(x, y);
}
