#ifndef LINEMODE_H
#define LINEMODE_H

#include <QGraphicsLineItem>
#include "abstractmode.h"

class LineMode : public AbstractMode
{
public:
    LineMode(QGraphicsScene*);
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    QGraphicsLineItem *line;
};

#endif // LINEMODE_H
