#include "../Overlay.h"

EllipseMode::EllipseMode(Overlay& overlay) : AbstractMode(overlay) {
}

void EllipseMode::init(int x, int y) {
    coords.x = x;
    coords.y = y;

    ellipse_ = new EllipseItem(overlay_, x, y);
    ellipse_->setPen(pen);

    overlay_.scene().addItem(ellipse_->graphicItems().at(0));
}

void EllipseMode::move(int x, int y) {
    int minX = qMin(x, coords.x);
    int minY = qMin(y, coords.y);
    int maxX = qMax(x, coords.x);
    int maxY = qMax(y, coords.y);

    auto ellipse = static_cast<QGraphicsEllipseItem*>(ellipse_->graphicItems().at(0));
    ellipse->setRect(minX, minY, maxX - minX, maxY - minY);
}

void EllipseMode::stop(int x, int y) {
    move(x, y);
}
