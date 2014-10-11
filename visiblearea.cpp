#include "visiblearea.h"

VisibleArea::VisibleArea(QGraphicsScene *scene) : scene(scene)
{
    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    // Black background (top, bottom, left, right)
    rectTop    = new QGraphicsRectItem;
    rectBottom = new QGraphicsRectItem;
    rectLeft   = new QGraphicsRectItem;
    rectRight  = new QGraphicsRectItem;

    rectTop->setOpacity(.5);
    rectBottom->setOpacity(.5);
    rectLeft->setOpacity(.5);
    rectRight->setOpacity(.5);

    rectTop->setPen(pen);
    rectBottom->setPen(pen);
    rectLeft->setPen(pen);
    rectRight->setPen(pen);

    rectTop->setBrush(brush);
    rectBottom->setBrush(brush);
    rectLeft->setBrush(brush);
    rectRight->setBrush(brush);

    // First rectangle fullscreen
    rectTop->setRect(0, 0, scene->width(), scene->height());

    scene->addItem(rectTop);
    scene->addItem(rectBottom);
    scene->addItem(rectLeft);
    scene->addItem(rectRight);
}

void VisibleArea::set(int x, int y, int width, int height)
{
    rectTop->setRect(0, 0, scene->width(), y);
    rectBottom->setRect(0, y + height, scene->width(), scene->height() - y - height);
    rectLeft->setRect(0, y, x, height);
    rectRight->setRect(x + width, y, scene->width() - x - width, height);

    area.x = x;
    area.y = y;
    area.width = width;
    area.height = height;
}

int VisibleArea::getX()
{
    return area.x;
}

int VisibleArea::getY()
{
    return area.y;
}

int VisibleArea::getWidth()
{
    return area.width;
}

int VisibleArea::getHeight()
{
    return area.height;
}
