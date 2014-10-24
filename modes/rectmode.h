#ifndef RECTMODE_H
#define RECTMODE_H

#include "abstractmode.h"

class RectMode : public AbstractMode
{
public:
    RectMode(QGraphicsScene*);
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    QGraphicsRectItem *rect;
};

#endif // RECTMODE_H
