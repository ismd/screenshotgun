#include <QtCore/qmath.h>
#include "ArrowMode.h"

ArrowMode::ArrowMode(QGraphicsScene& scene) : AbstractMode(scene) {
}

void ArrowMode::init(int x, int y) {
    line_ = new QGraphicsLineItem(x, y, x, y);
    line_->setPen(pen);

    path_ = new QGraphicsPathItem();
    QPen pathPen = QPen(pen);
    pathPen.setWidth(1);

    path_->setPen(pathPen);
    path_->setBrush(QBrush(pen.brush()));

    scene_.addItem(line_);
    scene_.addItem(path_);
}

void ArrowMode::move(int x, int y) {
    QLineF l = line_->line();
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

    line_->setLine(l);
    path_->setPath(painterPath);
}

void ArrowMode::stop(int x, int y) {
    move(x, y);
}
