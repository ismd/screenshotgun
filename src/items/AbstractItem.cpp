#include "AbstractItem.h"
#include "src/Context.h"

AbstractItem::AbstractItem() {
}

void AbstractItem::init(QMouseEvent* e) {
    Q_UNUSED(e);

    Context::getInstance().overlayView->scene.addItem(this);
}

void AbstractItem::move(QMouseEvent* e) {
    Q_UNUSED(e);
}

void AbstractItem::stop(QMouseEvent* e) {
    Q_UNUSED(e);

    move(e);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    Q_UNUSED(e);
    QGraphicsItemGroup::mousePressEvent(e);
}

void AbstractItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    Q_UNUSED(e);
    QGraphicsItemGroup::mouseMoveEvent(e);
}

void AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    Q_UNUSED(e);
    QGraphicsItemGroup::mouseReleaseEvent(e);
}
