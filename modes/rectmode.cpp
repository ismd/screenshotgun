#include <QGraphicsRectItem>
#include "rectmode.h"

RectMode::RectMode(QGraphicsScene *scene) : AbstractMode(scene)
{
}

void RectMode::init(int x, int y)
{
    QPen pen(Qt::red);
    QBrush brush(Qt::NoBrush);

    rect = new QGraphicsRectItem(x, y, 0, 0);
    rect->setPen(pen);
    rect->setBrush(brush);

    scene->addItem(rect);
}

void RectMode::move(int x, int y)
{
    QRectF r = rect->rect();
    int curX = rect->x();
    int curY = rect->y();

    r.setTopLeft(QPointF(qMin(x, curX), qMin(y, curY)));
    r.setTopRight(QPointF(qMax(x, curX), qMin(y, curY)));
    r.setBottomLeft(QPointF(qMin(x, curX), qMax(y, curY)));
    r.setBottomRight(QPointF(qMax(x, curX), qMax(y, curY)));

    rect->setRect(r);
}

void RectMode::stop(int x, int y)
{
}
