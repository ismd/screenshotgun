#ifndef SCREENSHOTGUN_PATHGRAPHICITEM_H
#define SCREENSHOTGUN_PATHGRAPHICITEM_H

#include <QGraphicsPathItem>
#include "AbstractGraphicItem.h"

class PathGraphicItem : public AbstractGraphicItem, public QGraphicsPathItem {

public:
    PathGraphicItem(AbstractItem* parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif //SCREENSHOTGUN_PATHGRAPHICITEM_H
