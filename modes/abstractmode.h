#ifndef ABSTRACTMODE_H
#define ABSTRACTMODE_H

#include <QMouseEvent>

#include "../visiblearea.h"

class AbstractMode
{
public:
    AbstractMode(VisibleArea *area);
    virtual ~AbstractMode();
    virtual void mousePress(QMouseEvent *e) = 0;
    virtual void mouseMove(QMouseEvent *e) = 0;
    virtual void mouseRelease(QMouseEvent *e) = 0;

protected:
    VisibleArea *visibleArea;
};

#endif // ABSTRACTMODE_H
