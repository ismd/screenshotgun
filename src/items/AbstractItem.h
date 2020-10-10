#pragma once

#include <QGraphicsItemGroup>
#include <QMouseEvent>

class AbstractItem : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    AbstractItem();

    /**
     * Pointer events
     */
    virtual void init(QMouseEvent*);
    virtual void move(QMouseEvent*);
    virtual void stop(QMouseEvent*);

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};
