#include <QCursor>
#include "../../Overlay.h"
#include "PathItem.h"

PathItem::PathItem(Overlay& overlay) : AbstractItem(overlay, this) {
}

void PathItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mousePressEvent(e);
    QGraphicsItem::mousePressEvent(e);
}

void PathItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mouseMoveEvent(e);
    QGraphicsItem::mouseMoveEvent(e);
}

void PathItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractItem::mouseReleaseEvent(e);
    QGraphicsItem::mouseReleaseEvent(e);
}

void PathItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractItem::hoverEnterEvent(e);
    QGraphicsItem::hoverEnterEvent(e);
}

void PathItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractItem::hoverLeaveEvent(e);
    QGraphicsItem::hoverLeaveEvent(e);
}
