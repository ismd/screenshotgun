#include "LineItem.h"

void LineItem::init(int x, int y) {
    QGraphicsLineItem::setLine(x, y, x, y);
}

void LineItem::move(int x, int y) {
    QLineF line = QGraphicsLineItem::line();
    line.setP2(QPointF(x, y));
    QGraphicsLineItem::setLine(line);
}

QGraphicsItem* LineItem::graphicsItem() {
    return this;
}

void LineItem::updatePen(const QPen& pen) {
    QGraphicsLineItem::setPen(pen);
}
