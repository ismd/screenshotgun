#ifndef SCREENSHOTGUN_ELLIPSEMODE_H
#define SCREENSHOTGUN_ELLIPSEMODE_H

#include "AbstractMode.h"

class EllipseMode : public AbstractMode {

public:
    EllipseMode(Scene&);
    virtual void init(int x, int y);
};

#endif // SCREENSHOTGUN_ELLIPSEMODE_H
