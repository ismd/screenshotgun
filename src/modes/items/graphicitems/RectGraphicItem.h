#ifndef SCREENSHOTGUN_RECTGRAPHICITEM_H
#define SCREENSHOTGUN_RECTGRAPHICITEM_H

#include <QGraphicsRectItem>
#include "AbstractGraphicItem.h"

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

#endif //SCREENSHOTGUN_RECTGRAPHICITEM_H
