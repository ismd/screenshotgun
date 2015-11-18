#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "VisibleAreaMode.h"
#include "../Toolbar.h"
#include "../App.h"

VisibleAreaMode::VisibleAreaMode(QGraphicsScene& scene, Toolbar& toolbar)
    : AbstractMode(scene),
      toolbar_(toolbar),
      initialized_(false) {

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

    area.x = x;
    area.y = y;
    area.width = 0;
    area.height = 0;

    set(x, y, 0, 0);
}

void VisibleAreaMode::move(int x, int y) {
    if (!initialized_) {
        area.x = x;
        area.y = y;
        area.width = 0;
        area.height = 0;
        set(area.x, area.y, area.width, area.height);
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

    set(area.x, area.y, area.width, area.height);
}

void VisibleAreaMode::stop(int x, int y) {
    toolbar_.appView().setMouseTracking(false);

    move(x, y);
    const int padding = 10;

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    // Width
    int formX = area.x + area.width + 28;
    int screenWidth = geo.width();
    int formWidth = toolbar_.width();

    if (formX + formWidth + padding > screenWidth) {
        formX = screenWidth - formWidth - padding;
    }

    // Height
    int formHeight = toolbar_.height();
    int formY = area.y + area.height / 2 - formHeight / 2;
    int screenHeight = geo.height();

    if (formY < padding) {
        formY = padding;
    } else if (formY + formHeight + padding > screenHeight) {
        formY = screenHeight - formHeight - padding;
    }

    toolbar_.setGeometry(formX, formY, formWidth, formHeight);
    toolbar_.show();
}

void VisibleAreaMode::set(int x, int y, int width, int height) {
    int sceneWidth = scene_.width(),
        sceneHeight = scene_.height();

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

bool VisibleAreaMode::initialized() {
    return initialized_;
}
