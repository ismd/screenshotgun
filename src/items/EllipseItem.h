#pragma once

#include "AbstractItem.h"

class EllipseItem : public AbstractItem {
    Q_OBJECT

public:
    EllipseItem(QMouseEvent*);

    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void stop(QMouseEvent*);

private:
    QGraphicsEllipseItem ellipse_;

    struct {
        int x;
        int y;
    } coords;
};
