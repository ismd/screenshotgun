#include "AbstractGraphicItem.h"

AbstractGraphicItem::AbstractGraphicItem(AbstractItem* parent) : parent_(parent) {
}

void AbstractGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    parent_->mousePressEvent(e);
}

void AbstractGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    parent_->mouseMoveEvent(e);
}

void AbstractGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    parent_->mouseReleaseEvent(e);
}

void AbstractGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    parent_->hoverEnterEvent(e);
}

void AbstractGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    parent_->hoverLeaveEvent(e);
}
