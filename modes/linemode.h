#ifndef LINEMODE_H
#define LINEMODE_H

#include "abstractmode.h"

class LineMode : public AbstractMode
{
public:
    LineMode(VisibleArea *area);
    void mousePress(QMouseEvent *e);
    void mouseMove(QMouseEvent *e);
    void mouseRelease(QMouseEvent *e);
};

#endif // LINEMODE_H
