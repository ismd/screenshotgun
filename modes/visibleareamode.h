#ifndef VISIBLEAREAMODE_H
#define VISIBLEAREAMODE_H

#include <QWidget>
#include <QGraphicsRectItem>

#include "abstractmode.h"

class VisibleAreaMode : public AbstractMode
{
public:
    VisibleAreaMode(QGraphicsScene*, QWidget*);
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    void set(int x, int y, int width, int height);

    QGraphicsRectItem *rectTop;
    QGraphicsRectItem *rectBottom;
    QGraphicsRectItem *rectLeft;
    QGraphicsRectItem *rectRight;

    struct {
        int x;
        int y;
        int width;
        int height;
    } area;

private:
    QWidget *form;
};

#endif // VISIBLEAREAMODE_H
