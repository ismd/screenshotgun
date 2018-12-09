#include "../../Overlay.h"

AbstractItem::AbstractItem(Overlay& overlay) : overlay_(overlay) {
}

AbstractItem::~AbstractItem() {
    for (auto item : graphicItems_) {
        overlay_.scene().removeItem(item);
    }
}

void AbstractItem::addGraphicItem(QGraphicsItem* item) {
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemClipsToShape);
    item->setAcceptHoverEvents(true);

    graphicItems_.append(item);
}

const QVector<QGraphicsItem*>& AbstractItem::graphicItems() const {
    return graphicItems_;
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    Q_UNUSED(e);

    overlay_.overlayView().setMovingItem(true);

    overlay_.setCursorLocked(false);
    overlay_.setCursor(Qt::ClosedHandCursor);
}

void AbstractItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    QPointF pos = e->pos();
    QPointF lastPos = e->lastPos();

    qreal diffX = pos.x() - lastPos.x();
    qreal diffY = pos.y() - lastPos.y();

    for (auto item : graphicItems()) {
        item->moveBy(diffX, diffY);
    }
}

void AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    Q_UNUSED(e);

    overlay_.overlayView().setMovingItem(false);
    overlay_.setCursor(Qt::CrossCursor);

    select();
}

void AbstractItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    Q_UNUSED(e);

    if (!overlay_.overlayView().movingItem()) {
        overlay_.setCursor(Qt::OpenHandCursor);
        overlay_.setCursorLocked(true);
    }
}

void AbstractItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    Q_UNUSED(e);
    overlay_.setCursorLocked(false);
}

void AbstractItem::select() {
}
