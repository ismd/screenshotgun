#include "ItemFactory.h"
#include "ArrowItem.h"
#include "EllipseItem.h"
#include "LineItem.h"
#include "RectItem.h"
#include "TextItem.h"

ItemFactory::ItemFactory() {
    pen_ = QPen(Qt::red, 3);
    pen_.setCapStyle(Qt::RoundCap);
}

AbstractItem* ItemFactory::createItem(ToolbarMode mode) {
    AbstractItem* item;

    switch (mode) {
        case ToolbarMode::ARROW:
            item = new ArrowItem();
            break;

        case ToolbarMode::ELLIPSE:
            item = new EllipseItem();
            break;

        case ToolbarMode::LINE:
            item = new LineItem();
            break;

        case ToolbarMode::RECT:
            item = new RectItem();
            break;

        case ToolbarMode::TEXT:
            item = new TextItem();
            break;
    }

    item->updatePen(pen_);
    return item;
}
