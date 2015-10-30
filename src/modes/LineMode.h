#ifndef SCREENSHOTGUN_LINEMODE_H
#define SCREENSHOTGUN_LINEMODE_H

#include <QGraphicsLineItem>
#include "AbstractMode.h"

class LineMode : public AbstractMode {

public:
    LineMode(QGraphicsScene&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

protected:
    QGraphicsLineItem* line;
};

#endif // SCREENSHOTGUN_LINEMODE_H
