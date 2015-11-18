#include "LineMode.h"

LineMode::LineMode(QGraphicsScene& scene) : AbstractMode(scene) {
}

void LineMode::init(int x, int y) {
    line_ = new QGraphicsLineItem(x, y, x, y);
    line_->setPen(pen);

    scene_.addItem(line_);
}

void LineMode::move(int x, int y) {
    QLineF l = line_->line();
    l.setP2(QPointF(x, y));
    line_->setLine(l);
}

void LineMode::stop(int x, int y) {
    move(x, y);
}
