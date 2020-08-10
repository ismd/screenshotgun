#include "ArrowItem.h"

#include <QPen>
#include <QtMath>

ArrowItem::ArrowItem(QMouseEvent* e) {
    line_.setPen({Qt::red, 3});
    path_.setPen({Qt::red});
    path_.setBrush(Qt::red);

    addToGroup(&line_);
    addToGroup(&path_);

    init(e);
}

void ArrowItem::init(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    line_.setLine(x, y, x, y);

    AbstractItem::init(e);
}

void ArrowItem::move(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    QLineF line = line_.line();
    line.setP2(QPointF(x, y));

    // Angle
    const qreal angle = qAtan(line.dy() / line.dx());
    const int length = 30;

    // Triangle
    QPainterPath painterPath;

    const int sign = line.dx() < 0 ? 1 : -1;

    painterPath.moveTo(x, y);
    painterPath.lineTo(x + qCos(angle - .25) * length * sign,
        y + qSin(angle - .25) * length * sign);
    painterPath.lineTo(x + qCos(angle + .25) * length * sign,
        y + qSin(angle + .25) * length * sign);
    painterPath.lineTo(x, y);

    line.setLength(line.length() - length);

    line_.setLine(line);
    path_.setPath(painterPath);

    AbstractItem::move(e);
}

void ArrowItem::stop(QMouseEvent* e) {
    AbstractItem::stop(e);
}
