#include "../Overlay.h"

LineMode::LineMode(Overlay& overlay) : AbstractMode(overlay) {
}

void LineMode::init(int x, int y) {
    line_ = new LineItem(overlay_, x, y);
    line_->setPen(pen);

    overlay_.scene().addItem(line_->graphicItems().at(0));
}

void LineMode::move(int x, int y) {
    auto line = static_cast<QGraphicsLineItem*>(line_->graphicItems().at(0));
    QLineF l = line->line();
    l.setP2(QPointF(x, y));
    line->setLine(l);
}

void LineMode::stop(int x, int y) {
    move(x, y);
}
