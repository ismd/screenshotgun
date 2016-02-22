#include "RectItem.h"

void RectItem::init(int x, int y) {
    coords_.x = x;
    coords_.y = y;
}

void RectItem::move(int x, int y) {
    int minX = qMin(x, coords_.x);
    int minY = qMin(y, coords_.y);
    int maxX = qMax(x, coords_.x);
    int maxY = qMax(y, coords_.y);

    QGraphicsRectItem::setRect(minX, minY, maxX - minX, maxY - minY);
}

QGraphicsItem* RectItem::graphicsItem() {
    return this;
}

void RectItem::updatePen(const QPen& pen) {
    QGraphicsRectItem::setPen(pen);
}
