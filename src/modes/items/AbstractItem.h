#ifndef SCREENSHOTGUN_ABSTRACTITEM_H
#define SCREENSHOTGUN_ABSTRACTITEM_H

#include <QGraphicsItem>

class Overlay;

class AbstractItem : public QObject {
    Q_OBJECT

public:
    explicit AbstractItem(Overlay&, QGraphicsItem*);
    void addLinkedItem(QGraphicsItem*);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

    Overlay& overlay_;
    QList<QGraphicsItem*> linkedItems_;
};

#endif //SCREENSHOTGUN_ABSTRACTITEM_H
