#pragma once

#include "AbstractMode.h"

#include <QWidget>
#include <QGraphicsRectItem>

class Toolbar;

enum class ResizeDirection {
    TOP,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    NONE
};

class VisibleAreaMode : public AbstractMode {

public:
    VisibleAreaMode(Overlay&, int maxWidth, int maxHeight, const QPoint& position);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

    void resizeInit(int x, int y);
    void resizeMove(int x, int y);
    void resizeStop(int x, int y);

    bool isResizablePosition(int x, int y);
    bool initialized();
    bool resizing();
    ResizeDirection resizablePosition(int x, int y);

    struct {
        int x;
        int y;
        int width;
        int height;
    } area;

private:
    void updateSize();
    void setArea(int x, int y, int width, int height);
    void updateToolbarPosition();

    QGraphicsRectItem rectTop_;
    QGraphicsRectItem rectBottom_;
    QGraphicsRectItem rectLeft_;
    QGraphicsRectItem rectRight_;

    QGraphicsLineItem lineTop_;
    QGraphicsLineItem lineBottom_;
    QGraphicsLineItem lineLeft_;
    QGraphicsLineItem lineRight_;

    bool initialized_;
    bool resizing_;

    struct {
        int x;
        int y;
        ResizeDirection direction;
    } resizeInfo_;

    int maxWidth_;
    int maxHeight_;
};
