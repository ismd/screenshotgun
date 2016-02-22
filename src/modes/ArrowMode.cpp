#include <QtCore/qmath.h>
#include "ArrowMode.h"

ArrowMode::ArrowMode(Scene& scene) : AbstractMode(scene) {
}

void ArrowMode::init(int x, int y) {
    item_ = itemFactory_.createItem(ToolbarMode::ARROW);
    AbstractMode::init(x, y);
}
