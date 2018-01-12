#ifndef SCREENSHOTGUN_LINEGRAPHICITEM_H
#define SCREENSHOTGUN_LINEGRAPHICITEM_H

#include <QGraphicsLineItem>
#include "AbstractGraphicItem.h"

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

#endif //SCREENSHOTGUN_LINEGRAPHICITEM_H
