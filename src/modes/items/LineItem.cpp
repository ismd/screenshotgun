#include <QCursor>
#include "LineItem.h"

LineItem::LineItem(Overlay& overlay, qreal x, qreal y)
    : QGraphicsLineItem(x, y, x, y), AbstractItem(overlay, this) {
}

void LineItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mousePressEvent(e);
    QGraphicsItem::mousePressEvent(e);
}

void LineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mouseMoveEvent(e);
    QGraphicsItem::mouseMoveEvent(e);
}

void LineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mouseReleaseEvent(e);
    QGraphicsItem::mouseReleaseEvent(e);
}

void LineItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractItem::hoverEnterEvent(e);
    QGraphicsItem::hoverEnterEvent(e);
}

void LineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractItem::hoverLeaveEvent(e);
    QGraphicsItem::hoverLeaveEvent(e);
}
