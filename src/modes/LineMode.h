#ifndef SCREENSHOTGUN_LINEMODE_H
#define SCREENSHOTGUN_LINEMODE_H

#include <QGraphicsLineItem>
#include "AbstractMode.h"

class LineMode : public AbstractMode {

public:
    LineMode(Scene&);
    virtual void init(int x, int y);
};

#endif // SCREENSHOTGUN_LINEMODE_H
