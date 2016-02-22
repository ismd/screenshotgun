#ifndef SCREENSHOTGUN_RECTMODE_H
#define SCREENSHOTGUN_RECTMODE_H

#include "AbstractMode.h"

class RectMode : public AbstractMode {

public:
    RectMode(Scene&);
    virtual void init(int x, int y);
};

#endif // SCREENSHOTGUN_RECTMODE_H
