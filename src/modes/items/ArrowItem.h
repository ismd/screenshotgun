#ifndef SCREENSHOTGUN_ARROWITEM_H
#define SCREENSHOTGUN_ARROWITEM_H

#include <QGraphicsLineItem>
#include "AbstractItem.h"

class ArrowItem : public AbstractItem, public QGraphicsLineItem {

public:
    virtual void init(int, int);
    virtual void move(int, int);

    virtual QGraphicsItem* graphicsItem();
    virtual void updatePen(const QPen& pen);

protected:
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

private:
    QGraphicsPathItem path_;
};

#endif //SCREENSHOTGUN_ARROWITEM_H
