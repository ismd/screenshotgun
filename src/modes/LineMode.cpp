#include "LineMode.h"

LineMode::LineMode(Scene& scene) : AbstractMode(scene) {
}

void LineMode::init(int x, int y) {
    item_ = itemFactory_.createItem(ToolbarMode::LINE);
    AbstractMode::init(x, y);
}
