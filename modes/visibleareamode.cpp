#include "../modes/visibleareamode.h"

VisibleAreaMode::VisibleAreaMode(VisibleArea *area) : AbstractMode(area)
{
}

void VisibleAreaMode::mousePress(QMouseEvent *e)
{
    visibleArea->set(e->x(), e->y(), 0, 0);
}

void VisibleAreaMode::mouseMove(QMouseEvent *e)
{
    int x = visibleArea->getX();
    int y = visibleArea->getY();

    int width = visibleArea->getWidth();
    int height = visibleArea->getHeight();

    int curX = e->x();
    int curY = e->y();

    if (curX > x && qAbs(x + width - curX) <= qAbs(x - curX)) {
        width = curX - x;
    } else {
        width = width + x - curX;
        x = curX;
    }

    if (curY > y && qAbs(y + height - curY) <= qAbs(y - curY)) {
        height = curY - y;
    } else {
        height = height + y - curY;
        y = curY;
    }

    visibleArea->set(x, y, width, height);
}

void VisibleAreaMode::mouseRelease(QMouseEvent *e)
{
}
