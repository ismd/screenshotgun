#include <QPen>
#include "RectGraphicItem.h"

RectGraphicItem::RectGraphicItem(AbstractItem* parent, qreal x, qreal y)
    : AbstractGraphicItem(parent),
      QGraphicsRectItem(x, y, 0, 0) {
}

QPainterPath RectGraphicItem::shape() const {
    QPainterPathStroker stroker;
    stroker.setWidth(pen().width());

    return stroker.createStroke(QGraphicsRectItem::shape());
}

void RectGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsRectItem::mousePressEvent(e);
}

void RectGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
}

void RectGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsRectItem::mouseReleaseEvent(e);
}

void RectGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsRectItem::hoverEnterEvent(e);
}

void RectGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsRectItem::hoverLeaveEvent(e);
}
