#include "EllipseMode.h"

EllipseMode::EllipseMode(Scene& scene) : AbstractMode(scene) {
}

void EllipseMode::init(int x, int y) {
    item_ = itemFactory_.createItem(ToolbarMode::ELLIPSE);
    AbstractMode::init(x, y);
}
