#include "linemode.h"

LineMode::LineMode(QGraphicsScene *scene) : AbstractMode(scene)
{
}

void LineMode::init(int x, int y)
{
    line = new QGraphicsLineItem(x, y, x, y);
    line->setPen(*_pen);

    scene->addItem(line);
}

void LineMode::move(int x, int y)
{
    QLineF l = line->line();
    l.setP2(QPointF(x, y));
    line->setLine(l);
}

void LineMode::stop(int x, int y)
{
    move(x, y);
}
