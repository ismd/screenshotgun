#pragma once

#include "AbstractMode.h"
#include "items/RectItem.h"

class RectMode : public AbstractMode {

public:
    RectMode(Overlay&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    RectItem* rect_;

    struct {
        int x;
        int y;
    } coords;
};
