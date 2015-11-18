#ifndef SCREENSHOTGUN_VISIBLEAREAMODE_H
#define SCREENSHOTGUN_VISIBLEAREAMODE_H

#include <QWidget>
#include <QGraphicsRectItem>
#include "AbstractMode.h"

class Toolbar;

class VisibleAreaMode : public AbstractMode {

public:
    VisibleAreaMode(QGraphicsScene&, Toolbar&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

    bool initialized();

    struct {
        int x;
        int y;
        int width;
        int height;
    } area;

private:
    void set(int x, int y, int width, int height);

    QGraphicsRectItem rectTop_;
    QGraphicsRectItem rectBottom_;
    QGraphicsRectItem rectLeft_;
    QGraphicsRectItem rectRight_;

    QGraphicsLineItem lineTop_;
    QGraphicsLineItem lineBottom_;
    QGraphicsLineItem lineLeft_;
    QGraphicsLineItem lineRight_;

    Toolbar& toolbar_;
    bool initialized_;
};

#endif // SCREENSHOTGUN_VISIBLEAREAMODE_H
