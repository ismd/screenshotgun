#include "linemode.h"

LineMode::LineMode(QGraphicsScene *scene) : AbstractMode(scene)
{
}

void LineMode::init(int x, int y)
{
    QPen pen(Qt::red);
    pen.setWidth(5);

    line = new QGraphicsLineItem(x, y, x, y);
    line->setPen(pen);

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
}
