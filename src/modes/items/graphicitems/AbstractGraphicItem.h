#ifndef SCREENSHOTGUN_ABSTRACTGRAPHICITEM_H
#define SCREENSHOTGUN_ABSTRACTGRAPHICITEM_H

#include "../AbstractItem.h"

class AbstractGraphicItem {

public:
    AbstractGraphicItem(AbstractItem* parent);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

private:
    AbstractItem* parent_;
};

#endif //SCREENSHOTGUN_ABSTRACTGRAPHICITEM_H
