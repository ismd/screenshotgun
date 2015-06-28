#ifndef ARROWMODE_H
#define ARROWMODE_H

#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include "linemode.h"

class ArrowMode : public AbstractMode
{
public:
    ArrowMode(QGraphicsScene*);
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

protected:
    QGraphicsLineItem *line;
    QGraphicsPathItem *path;
};

#endif // ARROWMODE_H
