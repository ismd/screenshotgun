#include "../Overlay.h"

RectMode::RectMode(Overlay& overlay) : AbstractMode(overlay) {
}

void RectMode::init(int x, int y) {
    coords.x = x;
    coords.y = y;

    rect_ = new RectItem(overlay_, x, y);
    rect_->setPen(pen);

    overlay_.addItem(rect_);
}

void RectMode::move(int x, int y) {
    int minX = qMin(x, coords.x);
    int minY = qMin(y, coords.y);
    int maxX = qMax(x, coords.x);
    int maxY = qMax(y, coords.y);

    auto rect = static_cast<QGraphicsRectItem*>(rect_->graphicItems().at(0));
    rect->setRect(minX, minY, maxX - minX, maxY - minY);
}

void RectMode::stop(int x, int y) {
    move(x, y);
}
