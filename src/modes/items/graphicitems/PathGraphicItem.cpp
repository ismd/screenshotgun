#include "PathGraphicItem.h"

PathGraphicItem::PathGraphicItem(AbstractItem* parent)
    : AbstractGraphicItem(parent) {
}

void PathGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsItem::mousePressEvent(e);
}

void PathGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
    QGraphicsItem::mouseMoveEvent(e);
}

void PathGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsItem::mouseReleaseEvent(e);
}

void PathGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsItem::hoverEnterEvent(e);
}

void PathGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsItem::hoverLeaveEvent(e);
}
