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
    overlay_.overlayView().setMovingItem(true);

    overlay_.setCursorLocked(false);
    overlay_.setCursor(Qt::ClosedHandCursor);
    Q_UNUSED(e);
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
    overlay_.overlayView().setMovingItem(false);
    overlay_.setCursor(Qt::CrossCursor);

    select();

    Q_UNUSED(e);
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

void AbstractItem::select() {

}
