#pragma once

#include <QVector>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Overlay;

class AbstractItem : public QObject {
    Q_OBJECT

public:
    explicit AbstractItem(Overlay&);
    ~AbstractItem();

    virtual void setPen(const QPen& pen)=0;

    void addGraphicItem(QGraphicsItem*);
    const QVector<QGraphicsItem*>& graphicItems() const;

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

    virtual void select();

protected:
    Overlay& overlay_;
    QVector<QGraphicsItem*> graphicItems_;
};
