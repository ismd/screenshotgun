#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include "../../Overlay.h"

LineItem::LineItem(Overlay& overlay, qreal x, qreal y)
    : QGraphicsLineItem(x, y, x, y),
      overlay_(overlay) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemClipsToShape);
    setAcceptHoverEvents(true);
}

void LineItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    overlay_.overlayView().setMovingItem(true);

    overlay_.setCursorLocked(false);
    overlay_.setCursor(Qt::ClosedHandCursor);

    QGraphicsItem::mousePressEvent(e);
}

void LineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    QGraphicsItem::mouseMoveEvent(e);
}

void LineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    overlay_.overlayView().setMovingItem(false);
    overlay_.setCursor(Qt::CrossCursor);

    QGraphicsItem::mouseReleaseEvent(e);
}

void LineItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    if (!overlay_.overlayView().movingItem()) {
        overlay_.setCursor(Qt::OpenHandCursor);
        overlay_.setCursorLocked(true);
    }

    Q_UNUSED(e);
}

void LineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    overlay_.setCursorLocked(false);
    Q_UNUSED(e);
}
