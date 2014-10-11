#ifndef VISIBLEAREAMODE_H
#define VISIBLEAREAMODE_H

#include "abstractmode.h"

class VisibleAreaMode : public AbstractMode
{
public:
    VisibleAreaMode(VisibleArea *area);
    void mousePress(QMouseEvent *e);
    void mouseMove(QMouseEvent *e);
    void mouseRelease(QMouseEvent *e);
};

#endif // VISIBLEAREAMODE_H
