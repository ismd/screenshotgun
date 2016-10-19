#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "VisibleAreaMode.h"
#include "../Toolbar.h"
#include "../App.h"

VisibleAreaMode::VisibleAreaMode(QGraphicsScene& scene, Toolbar& toolbar, int maxWidth, int maxHeight)
    : AbstractMode(scene),
      toolbar_(toolbar),
      maxWidth_(maxWidth),
      maxHeight_(maxHeight),
      initialized_(false),
      resizing_(false) {

    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    rectTop_.setOpacity(.65);
    rectBottom_.setOpacity(.65);
    rectLeft_.setOpacity(.65);
    rectRight_.setOpacity(.65);

    rectTop_.setPen(pen);
    rectBottom_.setPen(pen);
    rectLeft_.setPen(pen);
    rectRight_.setPen(pen);

    rectTop_.setBrush(brush);
    rectBottom_.setBrush(brush);
    rectLeft_.setBrush(brush);
    rectRight_.setBrush(brush);

    rectTop_.setZValue(1);
    rectBottom_.setZValue(1);
    rectLeft_.setZValue(1);
    rectRight_.setZValue(1);

    // First rectangle fullscreen
    rectTop_.setRect(0, 0, scene.width(), scene.height());

    scene.addItem(&rectTop_);
    scene.addItem(&rectBottom_);
    scene.addItem(&rectLeft_);
    scene.addItem(&rectRight_);

    QPen linePen;
    linePen.setWidthF(.2);
    linePen.setColor(QColor(230, 230, 230));

    lineTop_.setPen(linePen);
    lineBottom_.setPen(linePen);
    lineLeft_.setPen(linePen);
    lineRight_.setPen(linePen);

    lineTop_.setZValue(1);
    lineBottom_.setZValue(1);
    lineLeft_.setZValue(1);
    lineRight_.setZValue(1);

    scene.addItem(&lineTop_);
    scene.addItem(&lineBottom_);
    scene.addItem(&lineLeft_);
    scene.addItem(&lineRight_);
}

void VisibleAreaMode::init(int x, int y) {
    initialized_ = true;
    toolbar_.hide();
    setArea(x, y, 0, 0);
}

void VisibleAreaMode::move(int x, int y) {
    if (!initialized_) {
        setArea(x, y, 0, 0);
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

void VisibleAreaMode::stop(int x, int y) {
    move(x, y);
    updateToolbarPosition();
    toolbar_.show();
}

void VisibleAreaMode::resizeInit(int x, int y) {
    resizing_ = true;
    toolbar_.hide();

    resizeInfo_.x = x;
    resizeInfo_.y = y;

    // Detecting side
    resizeInfo_.direction = resizablePosition(x, y);
}

void VisibleAreaMode::resizeMove(int x, int y) {
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
    }

    resizeInfo_.x = x;
    resizeInfo_.y = y;
}

void VisibleAreaMode::resizeStop(int x, int y) {
    resizeMove(x, y);
    resizing_ = false;
    updateToolbarPosition();
    toolbar_.show();
}

void VisibleAreaMode::updateSize() {
    if (area.x + area.width > maxWidth_) {
        area.width = maxWidth_ - area.x;
    }

    if (area.y + area.height > maxHeight_) {
        area.height = maxHeight_ - area.y;
    }

    int x = area.x;
    int y = area.y;
    int width = area.width;
    int height = area.height;

    int sceneWidth = scene_.width();
    int sceneHeight = scene_.height();

    rectTop_.setRect(0, 0, sceneWidth, y);
    rectBottom_.setRect(0, y + height, sceneWidth, sceneHeight - y - height);
    rectLeft_.setRect(0, y, x, height);
    rectRight_.setRect(x + width, y, sceneWidth - x - width, height);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    int screenWidth = geo.width();
    int screenHeight = geo.height();

    // Horizontal and vertical lines
    if (0 == width && 0 == height) {
        lineTop_.setLine(0, y, screenWidth, y);
        lineLeft_.setLine(x, 0, x, screenHeight);
        return;
    }

    lineTop_.setLine(0, y - 1, screenWidth, y - 1);
    lineBottom_.setLine(0, y + height + 1, screenWidth, y + height + 1);
    lineLeft_.setLine(x - 1, 0, x - 1, screenHeight);
    lineRight_.setLine(x + width + 1, 0, x + width + 1, sceneHeight);
}

void VisibleAreaMode::setArea(int x, int y, int width, int height) {
    if (width < 0 || height < 0) {
        return;
    }

    area.x = x;
    area.y = y;
    area.width = width;
    area.height = height;
    updateSize();
}

void VisibleAreaMode::updateToolbarPosition() {
    const int padding = 10;

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    // Width
    int toolbarX = area.x + area.width + 28;
    int screenWidth = geo.width();
    int toolbarWidth = toolbar_.width();

    if (toolbarX + toolbarWidth + padding > screenWidth) {
        toolbarX = screenWidth - toolbarWidth - padding;
    }

    // Height
    int toolbarHeight = toolbar_.height();
    int toolbarY = area.y + area.height / 2 - toolbarHeight / 2;
    int screenHeight = geo.height();

    if (toolbarY < padding) {
        toolbarY = padding;
    } else if (toolbarY + toolbarHeight + padding > screenHeight) {
        toolbarY = screenHeight - toolbarHeight - padding;
    }

    toolbar_.setGeometry(toolbarX, toolbarY, toolbarWidth, toolbarHeight);
}

bool VisibleAreaMode::isResizablePosition(int x, int y) {
    return x <= area.x ||
           y <= area.y ||
           x >= area.x + area.width - 3 ||
           y >= area.y + area.height;
}

bool VisibleAreaMode::initialized() {
    return initialized_;
}

bool VisibleAreaMode::resizing() {
    return resizing_;
}

ResizeDirection VisibleAreaMode::resizablePosition(int x, int y) {
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
    } else if (x >= area.x + area.width - 3 && y >= area.y && y <= area.y + area.height) {
        return ResizeDirection::RIGHT;
    } else if (x >= area.x + area.width && y >= area.y + area.height) {
        return ResizeDirection::BOTTOM_RIGHT;
    }
}
