#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "VisibleAreaMode.h"
#include "../Toolbar.h"
#include "../App.h"

VisibleAreaMode::VisibleAreaMode(QGraphicsScene& scene, Toolbar& toolbar)
    : AbstractMode(scene),
      toolbar_(toolbar),
      initialized_(false),
      rectTop(new QGraphicsRectItem),
      rectBottom(new QGraphicsRectItem),
      rectLeft(new QGraphicsRectItem),
      rectRight(new QGraphicsRectItem),
      lineTop(new QGraphicsLineItem),
      lineBottom(new QGraphicsLineItem),
      lineLeft(new QGraphicsLineItem),
      lineRight(new QGraphicsLineItem) {

    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    rectTop->setOpacity(.65);
    rectBottom->setOpacity(.65);
    rectLeft->setOpacity(.65);
    rectRight->setOpacity(.65);

    rectTop->setPen(pen);
    rectBottom->setPen(pen);
    rectLeft->setPen(pen);
    rectRight->setPen(pen);

    rectTop->setBrush(brush);
    rectBottom->setBrush(brush);
    rectLeft->setBrush(brush);
    rectRight->setBrush(brush);

    rectTop->setZValue(1);
    rectBottom->setZValue(1);
    rectLeft->setZValue(1);
    rectRight->setZValue(1);

    // First rectangle fullscreen
    rectTop->setRect(0, 0, scene.width(), scene.height());

    scene.addItem(rectTop);
    scene.addItem(rectBottom);
    scene.addItem(rectLeft);
    scene.addItem(rectRight);

    QPen linePen;
    linePen.setWidthF(.2);
    linePen.setColor(QColor(230, 230, 230));

    lineTop->setPen(linePen);
    lineBottom->setPen(linePen);
    lineLeft->setPen(linePen);
    lineRight->setPen(linePen);

    lineTop->setZValue(1);
    lineBottom->setZValue(1);
    lineLeft->setZValue(1);
    lineRight->setZValue(1);

    scene.addItem(lineTop);
    scene.addItem(lineBottom);
    scene.addItem(lineLeft);
    scene.addItem(lineRight);
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

    rectTop->setRect(0, 0, sceneWidth, y);
    rectBottom->setRect(0, y + height, sceneWidth, sceneHeight - y - height);
    rectLeft->setRect(0, y, x, height);
    rectRight->setRect(x + width, y, sceneWidth - x - width, height);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    int screenWidth = geo.width();
    int screenHeight = geo.height();

    // Horizontal and vertical lines
    if (0 == width && 0 == height) {
        lineTop->setLine(0, y, screenWidth, y);
        lineLeft->setLine(x, 0, x, screenHeight);
        return;
    }

    lineTop->setLine(0, y - 1, screenWidth, y - 1);
    lineBottom->setLine(0, y + height + 1, screenWidth, y + height + 1);
    lineLeft->setLine(x - 1, 0, x - 1, screenHeight);
    lineRight->setLine(x + width + 1, 0, x + width + 1, sceneHeight);
}

bool VisibleAreaMode::initialized() {
    return initialized_;
}
