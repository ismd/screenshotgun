#pragma once

#include "AbstractGraphicItem.h"

#include <QGraphicsEllipseItem>

class EllipseGraphicItem : public AbstractGraphicItem, public QGraphicsEllipseItem {

public:
    EllipseGraphicItem(AbstractItem* parent, qreal x, qreal y);

    QPainterPath shape() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};
