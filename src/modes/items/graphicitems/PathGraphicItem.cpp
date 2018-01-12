#include "PathGraphicItem.h"

PathGraphicItem::PathGraphicItem(AbstractItem* parent)
    : AbstractGraphicItem(parent) {
}

void PathGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsPathItem::mousePressEvent(e);
}

void PathGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
}

void PathGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsPathItem::mouseReleaseEvent(e);
}

void PathGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsPathItem::hoverEnterEvent(e);
}

void PathGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsPathItem::hoverLeaveEvent(e);
}
