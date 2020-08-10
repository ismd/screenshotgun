#include "RectItem.h"

#include <QPen>

RectItem::RectItem(QMouseEvent* e) {
    rect_.setPen({Qt::red, 3});

    addToGroup(&rect_);

    init(e);
}

void RectItem::init(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    coords.x = x;
    coords.y = y;
    rect_.setRect(x, y, 1, 1);

    AbstractItem::init(e);
}

void RectItem::move(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();

    const int minX = qMin(x, coords.x);
    const int minY = qMin(y, coords.y);
    const int maxX = qMax(x, coords.x);
    const int maxY = qMax(y, coords.y);

    rect_.setRect(minX, minY, maxX - minX, maxY - minY);

    AbstractItem::move(e);
}

void RectItem::stop(QMouseEvent* e) {
    AbstractItem::stop(e);
}
