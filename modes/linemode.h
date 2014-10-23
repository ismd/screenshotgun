#ifndef LINEMODE_H
#define LINEMODE_H

#include "abstractmode.h"

class LineMode : public AbstractMode
{
public:
    LineMode(QGraphicsScene*);
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);
};

#endif // LINEMODE_H
