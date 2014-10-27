#ifndef ABSTRACTMODE_H
#define ABSTRACTMODE_H

#include <QGraphicsScene>

class AbstractMode
{
public:
    AbstractMode(QGraphicsScene*);
    virtual ~AbstractMode();

    virtual void init(int x, int y) = 0;
    virtual void move(int x, int y) = 0;
    virtual void stop(int x, int y) = 0;

protected:
    QGraphicsScene *scene;
    QPen* _pen;
};

#endif // ABSTRACTMODE_H
