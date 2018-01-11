#include "../../Overlay.h"

AbstractItem::AbstractItem(Overlay& overlay, QGraphicsItem* item) : overlay_(overlay) {
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemClipsToShape);
    item->setAcceptHoverEvents(true);
}

void AbstractItem::addLinkedItem(QGraphicsItem* item) {
    linkedItems_.append(item);
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    overlay_.overlayView().setMovingItem(true);

    overlay_.setCursorLocked(false);
    overlay_.setCursor(Qt::ClosedHandCursor);
}

void AbstractItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    QPointF pos = e->pos();
    QPointF lastPos = e->lastPos();

    qreal diffX = pos.x() - lastPos.x();
    qreal diffY = pos.y() - lastPos.y();

    for (auto item : linkedItems_) {
        item->moveBy(diffX, diffY);
    }
}

void AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    overlay_.overlayView().setMovingItem(false);
    overlay_.setCursor(Qt::CrossCursor);
}

void AbstractItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    if (!overlay_.overlayView().movingItem()) {
        overlay_.setCursor(Qt::OpenHandCursor);
        overlay_.setCursorLocked(true);
    }

    Q_UNUSED(e);
}

void AbstractItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    overlay_.setCursorLocked(false);
    Q_UNUSED(e);
}
