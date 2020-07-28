#pragma once

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
