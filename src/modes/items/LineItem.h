#ifndef SCREENSHOTGUN_LINEITEM_H
#define SCREENSHOTGUN_LINEITEM_H

#include <QGraphicsLineItem>

class Overlay;

class LineItem : public QGraphicsLineItem {

public:
    LineItem(Overlay&, qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

private:
    Overlay& overlay_;
};


#endif //SCREENSHOTGUN_LINEITEM_H
