#pragma once

#include "AbstractItem.h"

class ArrowItem : public AbstractItem {
    Q_OBJECT

public:
    ArrowItem(QMouseEvent*);

    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void stop(QMouseEvent*);

protected:
    QGraphicsLineItem line_;
    QGraphicsPathItem path_;
};
