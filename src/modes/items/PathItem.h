#ifndef SCREENSHOTGUN_PATHITEM_H
#define SCREENSHOTGUN_PATHITEM_H

#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include "AbstractItem.h"

class PathItem : public QGraphicsPathItem, public AbstractItem {

public:
    PathItem(Overlay&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif //SCREENSHOTGUN_PATHITEM_H
