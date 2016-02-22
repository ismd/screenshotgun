#ifndef SCREENSHOTGUN_ABSTRACTITEM_H
#define SCREENSHOTGUN_ABSTRACTITEM_H

#include "../../Scene.h"

class AbstractItem {

public:
    virtual void init(int, int);
    virtual void move(int, int);
    virtual void stop(int, int);

    virtual QGraphicsItem* graphicsItem()=0;
    virtual void updatePen(const QPen&)=0;
};

#endif //SCREENSHOTGUN_ABSTRACTITEM_H
