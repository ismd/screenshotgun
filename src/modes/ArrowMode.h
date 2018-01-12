#ifndef SCREENSHOTGUN_ARROWMODE_H
#define SCREENSHOTGUN_ARROWMODE_H

#include "AbstractMode.h"
#include "items/ArrowItem.h"

class ArrowMode : public AbstractMode {

public:
    ArrowMode(Overlay&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

protected:
    ArrowItem* arrow_;
};

#endif // SCREENSHOTGUN_ARROWMODE_H
