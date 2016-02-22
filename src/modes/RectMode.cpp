#include <QGraphicsRectItem>
#include "RectMode.h"

RectMode::RectMode(Scene& scene) : AbstractMode(scene) {
}

void RectMode::init(int x, int y) {
    item_ = itemFactory_.createItem(ToolbarMode::RECT);
    AbstractMode::init(x, y);
}
