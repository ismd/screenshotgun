#include "LineItem.h"

#include <QPen>

LineItem::LineItem(QMouseEvent* e) {
    line_.setPen({Qt::red, 3});
    addToGroup(&line_);

    init(e);
}

void LineItem::init(QMouseEvent* e) {
    line_.setPos(e->x(), e->y());

    AbstractItem::init(e);
}

void LineItem::move(QMouseEvent* e) {
    QLineF line = line_.line();
    line.setP2(QPointF(e->x() - line_.x(), e->y() - line_.y()));
    line_.setLine(line);

    AbstractItem::move(e);
}

void LineItem::stop(QMouseEvent* e) {
    AbstractItem::stop(e);
}
