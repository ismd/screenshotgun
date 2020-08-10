#include "VisibleAreaItem.h"
#include "src/Context.h"

VisibleAreaItem::VisibleAreaItem()
    : inited_(false),
      fixed_(false),
      resizing_(false),
      brush_(Qt::black),
      pen_(Qt::NoPen)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);

    area.x = 0;
    area.y = 0;
    area.width = 0;
    area.height = 0;

    rectTop_.setOpacity(.4);
    rectBottom_.setOpacity(.4);
    rectLeft_.setOpacity(.4);
    rectRight_.setOpacity(.4);

    rectTop_.setPen(pen_);
    rectBottom_.setPen(pen_);
    rectLeft_.setPen(pen_);
    rectRight_.setPen(pen_);

    rectTop_.setBrush(brush_);
    rectBottom_.setBrush(brush_);
    rectLeft_.setBrush(brush_);
    rectRight_.setBrush(brush_);

    linePen_.setWidth(1);
    linePen_.setColor(QColor(130, 130, 130));

    lineTop_.setPen(linePen_);
    lineBottom_.setPen(linePen_);
    lineLeft_.setPen(linePen_);
    lineRight_.setPen(linePen_);

    setZValue(1);

    addToGroup(&rectTop_);
    addToGroup(&rectBottom_);
    addToGroup(&rectLeft_);
    addToGroup(&rectRight_);

    addToGroup(&lineTop_);
    addToGroup(&lineBottom_);
    addToGroup(&lineLeft_);
    addToGroup(&lineRight_);

    Context& ctx = Context::getInstance();

    connect(ctx.app, &App::screenshotFinished, this, [&]() {
        inited_ = false;
        fixed_ = false;
        resizing_ = false;
    });
}

void VisibleAreaItem::init(QMouseEvent* e) {
    const int x = e->x();
    const int y = e->y();
    fixed_ = false;

    if (Context::getInstance().toolbar->mode() == ToolbarMode::VISIBLE_AREA) {
        inited_ = false;
    }

    if (inited_) {
        const ResizeDirection direction = resizeDirection(x, y);

        if (direction != ResizeDirection::NONE) {
            resizing_ = true;
            resizeInfo_.x = x;
            resizeInfo_.y = y;

            // Detecting side
            resizeInfo_.direction = direction;

            emit inited();
            return;
        }
    }

    inited_ = true;
    setArea(x, y, 0, 0);

    emit inited();
}

void VisibleAreaItem::move(QMouseEvent* e) {
    move(e->x(), e->y());
}

void VisibleAreaItem::move(int x, int y) {
    if (fixed_) {
        return;
    }

    if (!inited_) {
        setArea(x, y, 0, 0);
        return;
    }

    if (resizing_) {
        resizeMove(x, y);
        return;
    }

    if (x > area.x && qAbs(area.x + area.width - x) <= qAbs(area.x - x)) {
        area.width = x - area.x;
    } else {
        area.width = area.width + area.x - x;
        area.x = x;
    }

    if (y > area.y && qAbs(area.y + area.height - y) <= qAbs(area.y - y)) {
        area.height = y - area.y;
    } else {
        area.height = area.height + area.y - y;
        area.y = y;
    }

    updateSize();
}

void VisibleAreaItem::stop(QMouseEvent* e) {
    move(e);
    fixed_ = true;
    resizing_ = false;

    emit(stopped());
}

void VisibleAreaItem::addToScene() {
    Context::getInstance().overlayView->scene.addItem(this);
}

bool VisibleAreaItem::isInnerArea(int x, int y) const {
    return x > area.x &&
        y > area.y &&
        x < area.x + area.width &&
        y < area.y + area.height;
}

void VisibleAreaItem::updateSize() {
    Context& ctx = Context::getInstance();

    const QRect geo = ctx.overlayView->geometry();
    const int maxWidth = geo.width();
    const int maxHeight = geo.height();

    if (area.x + area.width > maxWidth) {
        area.width = maxWidth - area.x;
    }

    if (area.y + area.height > maxHeight) {
        area.height = maxHeight - area.y;
    }

    int x = area.x;
    int y = area.y;
    int width = area.width;
    int height = area.height;

    rectTop_.setRect(0, 0, maxWidth, y);
    rectBottom_.setRect(0, y + height, maxWidth, maxHeight - y - height);
    rectLeft_.setRect(0, y, x, height);
    rectRight_.setRect(x + width, y, maxWidth - x - width, height);

    // Horizontal and vertical lines
    if (width == 0 && height == 0) {
        lineTop_.setLine(0, y, maxWidth, y);
        lineLeft_.setLine(x, 0, x, maxHeight);
        lineBottom_.hide();
        lineRight_.hide();
        return;
    }

    lineTop_.setLine(0, y - 1, maxWidth, y - 1);
    lineBottom_.setLine(0, y + height + 1, maxWidth, y + height + 1);
    lineLeft_.setLine(x - 1, 0, x - 1, maxHeight);
    lineRight_.setLine(x + width + 1, 0, x + width + 1, maxHeight);
    lineBottom_.show();
    lineRight_.show();
}

void VisibleAreaItem::setArea(int x, int y, int width, int height) {
    if (width < 0 || height < 0) {
        return;
    }

    area.x = x;
    area.y = y;
    area.width = width;
    area.height = height;

    updateSize();
}

ResizeDirection VisibleAreaItem::resizeDirection(int x, int y) const {
    if (x <= area.x && y <= area.y) {
        return ResizeDirection::TOP_LEFT;
    } else if (x <= area.x && y >= area.y && y <= area.y + area.height) {
        return ResizeDirection::LEFT;
    } else if (x <= area.x && y >= area.y + area.height) {
        return ResizeDirection::BOTTOM_LEFT;
    } else if (x >= area.x && x <= area.x + area.width && y <= area.y) {
        return ResizeDirection::TOP;
    } else if (x >= area.x && x <= area.x + area.width && y >= area.y + area.height) {
        return ResizeDirection::BOTTOM;
    } else if (x >= area.x + area.width && y <= area.y) {
        return ResizeDirection::TOP_RIGHT;
    } else if (x >= area.x + area.width && y >= area.y && y <= area.y + area.height) {
        return ResizeDirection::RIGHT;
    } else if (x >= area.x + area.width && y >= area.y + area.height) {
        return ResizeDirection::BOTTOM_RIGHT;
    }

    return ResizeDirection::NONE;
}

void VisibleAreaItem::resizeMove(int x, int y) {
    int diffX = x - resizeInfo_.x;
    int diffY = y - resizeInfo_.y;

    switch (resizeInfo_.direction) {
        case ResizeDirection::TOP_LEFT:
            setArea(area.x + diffX, area.y + diffY, area.width - diffX, area.height - diffY);
            break;

        case ResizeDirection::LEFT:
            setArea(area.x + diffX, area.y, area.width - diffX, area.height);
            break;

        case ResizeDirection::BOTTOM_LEFT:
            setArea(area.x + diffX, area.y, area.width - diffX, area.height + diffY);
            break;

        case ResizeDirection::TOP:
            setArea(area.x, area.y + diffY, area.width, area.height - diffY);
            break;

        case ResizeDirection::BOTTOM:
            setArea(area.x, area.y, area.width, area.height + diffY);
            break;

        case ResizeDirection::TOP_RIGHT:
            setArea(area.x, area.y + diffY, area.width + diffX, area.height - diffY);
            break;

        case ResizeDirection::RIGHT:
            setArea(area.x, area.y, area.width + diffX, area.height);
            break;

        case ResizeDirection::BOTTOM_RIGHT:
            setArea(area.x, area.y, area.width + diffX, area.height + diffY);
            break;

        case ResizeDirection::NONE:
            break;
    }

    resizeInfo_.x = x;
    resizeInfo_.y = y;
}
