#include <QtMath>
#include "../Overlay.h"

ArrowMode::ArrowMode(Overlay& overlay) : AbstractMode(overlay) {
}

void ArrowMode::init(int x, int y) {
    arrow_ = new ArrowItem(overlay_, x, y);
    arrow_->setPen(pen);

    overlay_.addItem(arrow_);
}

void ArrowMode::move(int x, int y) {
    auto line = static_cast<QGraphicsLineItem*>(arrow_->graphicItems().at(0));
    QLineF l = line->line();
    l.setP2(QPointF(x, y));

    // Angle
    qreal angle = qAtan(l.dy() / l.dx());
    int length = 30;

    // Triangle
    QPainterPath painterPath;

    int sign = l.dx() < 0 ? 1 : -1;

    painterPath.moveTo(x, y);
    painterPath.lineTo(x + qCos(angle - .25) * length * sign,
                       y + qSin(angle - .25) * length * sign);
    painterPath.lineTo(x + qCos(angle + .25) * length * sign,
                       y + qSin(angle + .25) * length * sign);
    painterPath.lineTo(x, y);

    l.setP2(QPointF(x + qCos(angle) * 5 * sign,
                    y + qSin(angle) * 5 * sign));

    line->setLine(l);

    auto path = static_cast<QGraphicsPathItem*>(arrow_->graphicItems().at(1));
    path->setPath(painterPath);
}

void ArrowMode::stop(int x, int y) {
    move(x, y);
}
