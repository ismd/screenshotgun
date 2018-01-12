#include <QPen>
#include "EllipseGraphicItem.h"

EllipseGraphicItem::EllipseGraphicItem(AbstractItem* parent, qreal x, qreal y)
    : AbstractGraphicItem(parent),
      QGraphicsEllipseItem(x, y, 0, 0) {
}

QPainterPath EllipseGraphicItem::shape() const {
    QPainterPathStroker stroker;
    stroker.setWidth(pen().width());

    return stroker.createStroke(QGraphicsEllipseItem::shape());
}

void EllipseGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsEllipseItem::mousePressEvent(e);
}

void EllipseGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
}

void EllipseGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsEllipseItem::mouseReleaseEvent(e);
}

void EllipseGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsEllipseItem::hoverEnterEvent(e);
}

void EllipseGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsEllipseItem::hoverLeaveEvent(e);
}
