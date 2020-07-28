#pragma once

#include "AbstractGraphicItem.h"

#include <QGraphicsPathItem>

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
