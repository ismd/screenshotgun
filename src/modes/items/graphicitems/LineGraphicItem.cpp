#include "LineGraphicItem.h"

LineGraphicItem::LineGraphicItem(AbstractItem* parent, qreal x, qreal y)
    : AbstractGraphicItem(parent),
      QGraphicsLineItem(x, y, x, y) {
}

void LineGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsItem::mousePressEvent(e);
}

void LineGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
}

void LineGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsItem::mouseReleaseEvent(e);
}

void LineGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsItem::hoverEnterEvent(e);
}

void LineGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsItem::hoverLeaveEvent(e);
}
