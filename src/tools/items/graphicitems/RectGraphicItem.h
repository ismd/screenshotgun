#pragma once

#include "AbstractGraphicItem.h"

#include <QGraphicsRectItem>

class RectGraphicItem : public AbstractGraphicItem, public QGraphicsRectItem {

public:
    RectGraphicItem(AbstractItem* parent, qreal x, qreal y);

    QPainterPath shape() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};
