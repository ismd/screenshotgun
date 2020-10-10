#include "EllipseItem.h"

#include <QPen>

EllipseItem::EllipseItem(QMouseEvent* e) {
    ellipse_.setPen({Qt::red, 3});

    addToGroup(&ellipse_);

    init(e);
}

void EllipseItem::init(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    coords.x = x;
    coords.y = y;
    ellipse_.setRect(x, y, 1, 1);

    AbstractItem::init(e);
}

void EllipseItem::move(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    const int minX = qMin(x, coords.x);
    const int minY = qMin(y, coords.y);
    const int maxX = qMax(x, coords.x);
    const int maxY = qMax(y, coords.y);

    ellipse_.setRect(minX, minY, maxX - minX, maxY - minY);

    AbstractItem::move(e);
}

void EllipseItem::stop(QMouseEvent* e) {
    AbstractItem::stop(e);
}
