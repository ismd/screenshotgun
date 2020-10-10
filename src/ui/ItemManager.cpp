#include "ItemManager.h"
#include "src/Context.h"
#include "src/items/ArrowItem.h"
#include "src/items/EllipseItem.h"
#include "src/items/LineItem.h"
#include "src/items/RectItem.h"

ItemManager::ItemManager() : current_(&visibleAreaItem) {
    const Context& ctx = Context::getInstance();

    connect(ctx.overlayView, &OverlayView::hided, this, [&]() {
        qDeleteAll(items_);
        items_.clear();
    });
}

void ItemManager::init(QMouseEvent* e) {
    const Context& ctx = Context::getInstance();
    const ToolbarMode mode = ctx.toolbar->selected();

    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            current_ = &visibleAreaItem;
            visibleAreaItem.init(e);
            break;

        case ToolbarMode::ARROW:
            current_ = new ArrowItem(e);
            break;

        case ToolbarMode::LINE:
            current_ = new LineItem(e);
            break;

        case ToolbarMode::RECT:
            current_ = new RectItem(e);
            break;

        case ToolbarMode::ELLIPSE:
            current_ = new EllipseItem(e);
            break;

        default:
            break;
    }

    if (current_ != &visibleAreaItem) {
        items_.insert(current_);
    }

    emit(inited(mode));
}

void ItemManager::move(QMouseEvent* e) {
    current_->move(e);
}

void ItemManager::stop(QMouseEvent* e) {
    current_->stop(e);
    current_ = &visibleAreaItem;
    emit(stopped(Context::getInstance().toolbar->selected()));
}
