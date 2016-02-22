#ifndef SCREENSHOTGUN_ELLIPSEITEM_H
#define SCREENSHOTGUN_ELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include "AbstractItem.h"

class EllipseItem : public AbstractItem, public QGraphicsEllipseItem {

public:
    virtual void init(int, int);
    virtual void move(int, int);

    virtual QGraphicsItem* graphicsItem();
    virtual void updatePen(const QPen& pen);

private:
    struct {
        int x;
        int y;
    } coords_;
};

#endif //SCREENSHOTGUN_ELLIPSEITEM_H
