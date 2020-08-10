#pragma once

#include "AbstractItem.h"

class RectItem : public AbstractItem {
    Q_OBJECT

public:
    RectItem(QMouseEvent*);

    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void stop(QMouseEvent*);

private:
    QGraphicsRectItem rect_;
    struct {
        int x;
        int y;
    } coords;
};
