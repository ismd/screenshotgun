#pragma once

#include "AbstractMode.h"
#include "items/EllipseItem.h"

class EllipseMode : public AbstractMode {

public:
    EllipseMode(Overlay&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    EllipseItem* ellipse_;

    struct {
        int x;
        int y;
    } coords;
};
