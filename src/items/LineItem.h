#pragma once

#include "AbstractItem.h"

class LineItem : public AbstractItem {
    Q_OBJECT

public:
    LineItem(QMouseEvent*);

    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void stop(QMouseEvent*);

protected:
    QGraphicsLineItem line_;
};
