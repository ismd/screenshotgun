#pragma once

#include "AbstractItem.h"

#include <QGraphicsRectItem>
#include <QPen>

enum class ResizeDirection {
    TOP,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    NONE,
};

class VisibleAreaItem : public AbstractItem {
    Q_OBJECT

public:
    VisibleAreaItem();

    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void move(int x, int y);
    void stop(QMouseEvent*);

    void addToScene();
    bool isInnerArea(int x, int y) const;
    ResizeDirection resizeDirection(int x, int y) const;

    struct {
      int x;
      int y;
      int width;
      int height;
    } area;

signals:
    void inited();
    void stopped();

private:
    void updateSize();
    void setArea(int x, int y, int width, int height);
    void resizeMove(int x, int y);

    QGraphicsRectItem rectTop_;
    QGraphicsRectItem rectBottom_;
    QGraphicsRectItem rectLeft_;
    QGraphicsRectItem rectRight_;

    QGraphicsLineItem lineTop_;
    QGraphicsLineItem lineBottom_;
    QGraphicsLineItem lineLeft_;
    QGraphicsLineItem lineRight_;

    bool inited_;
    bool fixed_;
    bool resizing_;

    struct {
        int x;
        int y;
        ResizeDirection direction;
    } resizeInfo_;

    QPen linePen_;
    QBrush brush_;
    QPen pen_;
};
