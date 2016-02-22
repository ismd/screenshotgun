#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "VisibleAreaMode.h"
#include "../App.h"

VisibleAreaMode::VisibleAreaMode(Scene& scene, Toolbar& toolbar, int maxWidth, int maxHeight)
    : AbstractMode(scene),
      toolbar_(toolbar),
      maxWidth_(maxWidth),
      maxHeight_(maxHeight),
      initialized_(false),
      rectTopLeft_(*this, ResizeDirection::TOP_LEFT),
      rectTop_(*this, ResizeDirection::TOP),
      rectTopRight_(*this, ResizeDirection::TOP_RIGHT),
      rectLeft_(*this, ResizeDirection::LEFT),
      rectRight_(*this, ResizeDirection::RIGHT),
      rectBottomLeft_(*this, ResizeDirection::BOTTOM_LEFT),
      rectBottom_(*this, ResizeDirection::BOTTOM),
      rectBottomRight_(*this, ResizeDirection::BOTTOM_RIGHT) {

    connect(&scene.sceneManager(), SIGNAL(modeChanged(ToolbarMode)),
            this, SLOT(modeChanged(ToolbarMode)));

    activeRect_.setPen(Qt::NoPen);
    scene_.addItem(&activeRect_);

    prepareRect(rectTopLeft_);
    prepareRect(rectTop_);
    prepareRect(rectTopRight_);
    prepareRect(rectLeft_);
    prepareRect(rectRight_);
    prepareRect(rectBottomLeft_);
    prepareRect(rectBottom_);
    prepareRect(rectBottomRight_);

    fullscreenRect_ = &rectTopLeft_;
    fullscreenRect_->setRect(0, 0, scene_.width(), scene_.height());

    prepareLine(lineTopLeft1_);
    prepareLine(lineTopLeft2_);
    prepareLine(lineTopRight1_);
    prepareLine(lineTopRight2_);
    prepareLine(lineBottomLeft1_);
    prepareLine(lineBottomLeft2_);
    prepareLine(lineBottomRight1_);
    prepareLine(lineBottomRight2_);
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

void VisibleAreaMode::modeChanged(ToolbarMode mode) {
    if (mode == ToolbarMode::TEXT) {
        activeRect_.setCursor(Qt::IBeamCursor);
    } else {
        activeRect_.setCursor(Qt::CrossCursor);
    }

    if (mode == ToolbarMode::VISIBLE_AREA) {
        rectTopLeft_.setCursor(Qt::CrossCursor);
        rectTop_.setCursor(Qt::CrossCursor);
        rectTopRight_.setCursor(Qt::CrossCursor);
        rectLeft_.setCursor(Qt::CrossCursor);
        rectRight_.setCursor(Qt::CrossCursor);
        rectBottomLeft_.setCursor(Qt::CrossCursor);
        rectBottom_.setCursor(Qt::CrossCursor);
        rectBottomRight_.setCursor(Qt::CrossCursor);
    } else {
        rectTopLeft_.setCursor(Qt::SizeFDiagCursor);
        rectTop_.setCursor(Qt::SizeVerCursor);
        rectTopRight_.setCursor(Qt::SizeBDiagCursor);
        rectLeft_.setCursor(Qt::SizeHorCursor);
        rectRight_.setCursor(Qt::SizeHorCursor);
        rectBottomLeft_.setCursor(Qt::SizeBDiagCursor);
        rectBottom_.setCursor(Qt::SizeVerCursor);
        rectBottomRight_.setCursor(Qt::SizeFDiagCursor);
    }
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

    if (!initialized_) {
        lineTopLeft1_.setLine(0, y, x, y);
        lineTopLeft2_.setLine(x, 0, x, y);
        lineBottomLeft1_.setLine(x, y, sceneWidth, y);
        lineBottomLeft2_.setLine(x, y, x, sceneHeight);
    } else {
        width = width > 0 ? width : 1;
        height = height > 0 ? height : 1;

        activeRect_.setRect(x, y, width, height);

        rectTopLeft_.setRect(0, 0, x, y);
        rectTop_.setRect(x, 0, width, y);
        rectTopRight_.setRect(x + width, 0, sceneWidth - x - width, y);
        rectLeft_.setRect(0, y, x, height);
        rectRight_.setRect(x + width, y, sceneWidth - x - width, height);
        rectBottomLeft_.setRect(0, y + height, x, sceneHeight - y - height);
        rectBottom_.setRect(x, y + height, width, sceneHeight - y - height);
        rectBottomRight_.setRect(x + width, y + height, sceneWidth - x - width, sceneHeight - y - height);

        lineTopLeft1_.setLine(0, y, x, y);
        lineTopLeft2_.setLine(x, 0, x, y);
        lineTopRight1_.setLine(x + width, 0, x + width, y);
        lineTopRight2_.setLine(x + width, y, sceneWidth, y);
        lineBottomLeft1_.setLine(0, y + height, x, y + height);
        lineBottomLeft2_.setLine(x, y + height, x, sceneWidth);
        lineBottomRight1_.setLine(x + width, y + height, x + width, sceneWidth);
        lineBottomRight2_.setLine(x + width, y + height, sceneWidth, y + height);
    }
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

    QDesktopWidget* desktop = QApplication::desktop();
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

void VisibleAreaMode::prepareRect(QGraphicsRectItem& rect) {
    rect.setOpacity(.65);
    rect.setPen(Qt::NoPen);
    rect.setBrush(QBrush(Qt::black));
    rect.setZValue(1);

    scene_.addItem(&rect);
}

void VisibleAreaMode::prepareLine(QGraphicsLineItem& line) {
    line.setPen(QPen(QColor(180, 180, 180)));
    line.setZValue(1);

    scene_.addItem(&line);
}

bool VisibleAreaMode::initialized() {
    return initialized_;
}

void VisibleAreaMode::resizeArea(int x, int y, int width, int height) {
    setArea(area.x + x, area.y + y, area.width - x + width, area.height - y + height);
}

Toolbar& VisibleAreaMode::toolbar() {
    return toolbar_;
}
