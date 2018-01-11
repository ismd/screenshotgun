#include <QGraphicsEllipseItem>
#include "../Overlay.h"

EllipseMode::EllipseMode(Overlay& overlay) : AbstractMode(overlay) {
}

void EllipseMode::init(int x, int y) {
    coords.x = x;
    coords.y = y;

    QBrush brush(Qt::NoBrush);

    ellipse_ = new QGraphicsEllipseItem();
    ellipse_->setPen(pen);
    ellipse_->setBrush(brush);

    overlay_.scene().addItem(ellipse_);
}

void EllipseMode::move(int x, int y) {
    int minX = qMin(x, coords.x);
    int minY = qMin(y, coords.y);
    int maxX = qMax(x, coords.x);
    int maxY = qMax(y, coords.y);

    ellipse_->setRect(minX, minY, maxX - minX, maxY - minY);
}

void EllipseMode::stop(int x, int y) {
    move(x, y);
}
