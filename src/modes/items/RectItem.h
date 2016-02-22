#ifndef SCREENSHOTGUN_RECTITEM_H
#define SCREENSHOTGUN_RECTITEM_H

#include <QGraphicsRectItem>
#include "AbstractItem.h"

class RectItem : public AbstractItem, public QGraphicsRectItem {

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

#endif //SCREENSHOTGUN_RECTITEM_H
