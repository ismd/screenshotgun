#pragma once

#include "AbstractGraphicItem.h"

#include <QGraphicsLineItem>

class LineGraphicItem : public AbstractGraphicItem, public QGraphicsLineItem {

public:
    LineGraphicItem(AbstractItem* parent, qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};
