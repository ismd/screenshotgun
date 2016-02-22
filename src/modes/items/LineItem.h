#ifndef SCREENSHOTGUN_LINEITEM_H
#define SCREENSHOTGUN_LINEITEM_H

#include <QGraphicsLineItem>
#include "AbstractItem.h"

class LineItem : public AbstractItem, public QGraphicsLineItem {

public:
    virtual void init(int, int);
    virtual void move(int, int);

    virtual QGraphicsItem* graphicsItem();
    virtual void updatePen(const QPen& pen);
};

#endif //SCREENSHOTGUN_LINEITEM_H
