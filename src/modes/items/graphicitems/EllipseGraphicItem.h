#ifndef SCREENSHOTGUN_ELLIPSEGRAPHICITEM_H
#define SCREENSHOTGUN_ELLIPSEGRAPHICITEM_H

#include <QGraphicsEllipseItem>
#include "AbstractGraphicItem.h"

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

#endif //SCREENSHOTGUN_ELLIPSEGRAPHICITEM_H
