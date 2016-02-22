#ifndef SCREENSHOTGUN_ARROWMODE_H
#define SCREENSHOTGUN_ARROWMODE_H

#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include "AbstractMode.h"

class ArrowMode : public AbstractMode {

public:
    ArrowMode(Scene&);
    virtual void init(int x, int y);
};

#endif // SCREENSHOTGUN_ARROWMODE_H
