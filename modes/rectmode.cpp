#include <QGraphicsRectItem>
#include "rectmode.h"

RectMode::RectMode(QGraphicsScene *scene) : AbstractMode(scene)
{
}

void RectMode::init(int x, int y)
{
    coords.x = x;
    coords.y = y;

    QBrush brush(Qt::NoBrush);

    rect = new QGraphicsRectItem;
    rect->setPen(*_pen);
    rect->setBrush(brush);

    scene->addItem(rect);
}

void RectMode::move(int x, int y)
{
    int minX = qMin(x, coords.x);
    int minY = qMin(y, coords.y);
    int maxX = qMax(x, coords.x);
    int maxY = qMax(y, coords.y);

    rect->setRect(minX, minY, maxX - minX, maxY - minY);
}

void RectMode::stop(int x, int y)
{
    move(x, y);
}
