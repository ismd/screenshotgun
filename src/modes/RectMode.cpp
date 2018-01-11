#include <QGraphicsRectItem>
#include "../Overlay.h"

RectMode::RectMode(Overlay& overlay) : AbstractMode(overlay) {
}

void RectMode::init(int x, int y) {
    coords.x = x;
    coords.y = y;

    QBrush brush(Qt::NoBrush);

    rect_ = new QGraphicsRectItem();
    rect_->setPen(pen);
    rect_->setBrush(brush);

    overlay_.scene().addItem(rect_);
}

void RectMode::move(int x, int y) {
    int minX = qMin(x, coords.x);
    int minY = qMin(y, coords.y);
    int maxX = qMax(x, coords.x);
    int maxY = qMax(y, coords.y);

    rect_->setRect(minX, minY, maxX - minX, maxY - minY);
}

void RectMode::stop(int x, int y) {
    move(x, y);
}
