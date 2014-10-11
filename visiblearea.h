#ifndef VISIBLEAREA_H
#define VISIBLEAREA_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class VisibleArea
{
public:
    VisibleArea(QGraphicsScene*);
    void set(int x, int y, int width, int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();

private:
    QGraphicsScene *scene;

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
};

#endif // VISIBLEAREA_H
