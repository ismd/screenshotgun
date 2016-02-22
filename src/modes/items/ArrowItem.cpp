#include "ArrowItem.h"

void ArrowItem::init(int x, int y) {
    QGraphicsLineItem::setLine(x, y, x, y);
}

void ArrowItem::move(int x, int y) {
    QLineF line = QGraphicsLineItem::line();
    line.setP2(QPointF(x, y));

    // Angle
    qreal angle = qAtan(line.dy() / line.dx());
    const int length = 30;

    // Triangle
    QPainterPath painterPath;

    int sign = line.dx() < 0 ? 1 : -1;

    painterPath.moveTo(x, y);
    painterPath.lineTo(x + qCos(angle - .25) * length * sign,
                       y + qSin(angle - .25) * length * sign);
    painterPath.lineTo(x + qCos(angle + .25) * length * sign,
                       y + qSin(angle + .25) * length * sign);
    painterPath.lineTo(x, y);

    line.setP2(QPointF(x + qCos(angle) * 5 * sign,
                       y + qSin(angle) * 5 * sign));

    QGraphicsLineItem::setLine(line);
    path_.setPath(painterPath);
}

QGraphicsItem* ArrowItem::graphicsItem() {
    return this;
}

void ArrowItem::updatePen(const QPen& pen) {
    QGraphicsLineItem::setPen(pen);
    QPen pathPen(pen);
    pathPen.setWidth(1);
    path_.setPen(pathPen);
    path_.setBrush(pen.brush());
}

QRectF ArrowItem::boundingRect() const {
    return QGraphicsLineItem::boundingRect();
}

QPainterPath ArrowItem::shape() const {
    return QGraphicsLineItem::shape();
}

void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QGraphicsLineItem::paint(painter, option, widget);
    path_.paint(painter, option, widget);
}
