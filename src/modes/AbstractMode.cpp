#include "AbstractMode.h"
#include "items/LineItem.h"

ItemFactory AbstractMode::itemFactory_;

AbstractMode::AbstractMode(Scene& scene) : scene_(scene) {
}

Scene& AbstractMode::scene() {
    return scene_;
}

void AbstractMode::init(int x, int y) {
    item_->init(x, y);
    scene_.addItem(item_->graphicsItem());
}

void AbstractMode::move(int x, int y) {
    item_->move(x, y);
}

void AbstractMode::stop(int x, int y) {
    item_->stop(x, y);

    QGraphicsItem* item = item_->graphicsItem();
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    item->setCursor(Qt::DragMoveCursor);
    item->setSelected(true);
}
