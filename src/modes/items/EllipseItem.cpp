#include "EllipseItem.h"

void EllipseItem::init(int x, int y) {
    coords_.x = x;
    coords_.y = y;
}

void EllipseItem::move(int x, int y) {
    int minX = qMin(x, coords_.x);
    int minY = qMin(y, coords_.y);
    int maxX = qMax(x, coords_.x);
    int maxY = qMax(y, coords_.y);

    QGraphicsEllipseItem::setRect(minX, minY, maxX - minX, maxY - minY);
}

QGraphicsItem* EllipseItem::graphicsItem() {
    return this;
}

void EllipseItem::updatePen(const QPen& pen) {
    QGraphicsEllipseItem::setPen(pen);
}
