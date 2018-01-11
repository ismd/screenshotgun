#ifndef SCREENSHOTGUN_ARROWMODE_H
#define SCREENSHOTGUN_ARROWMODE_H

#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include "LineMode.h"

class ArrowMode : public AbstractMode {

public:
    ArrowMode(Overlay&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

protected:
    QGraphicsLineItem* line_;
    QGraphicsPathItem* path_;
};

#endif // SCREENSHOTGUN_ARROWMODE_H
