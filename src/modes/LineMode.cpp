#include "../Overlay.h"

LineMode::LineMode(Overlay& overlay) : AbstractMode(overlay) {
}

void LineMode::init(int x, int y) {
    line_ = new LineItem(overlay_, x, y);
    line_->setPen(pen);

    overlay_.scene().addItem(line_);
}

void LineMode::move(int x, int y) {
    QLineF l = line_->line();
    l.setP2(QPointF(x, y));
    line_->setLine(l);
}

void LineMode::stop(int x, int y) {
    move(x, y);
}
