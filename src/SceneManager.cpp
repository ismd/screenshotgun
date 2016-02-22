#include <QApplication>
#include <QDesktopWidget>
#include "AppView.h"
#include "SceneManager.h"

SceneManager::SceneManager(AppView& appView)
    : appView_(appView),
      scene_(*this),
      selection_(0),
      visibleAreaMode_(0),
      lineMode_(scene_),
      arrowMode_(scene_),
      rectMode_(scene_),
      ellipseMode_(scene_),
      textMode_(scene_) {
    connect(&scene_, SIGNAL(selectionChanged()),
            this, SLOT(selectItem()));
}

SceneManager::~SceneManager() {
    delete visibleAreaMode_;
}

AppView& SceneManager::appView() {
    return appView_;
}

Scene& SceneManager::scene() {
    return scene_;
}

QGraphicsItem* SceneManager::getSelection() {
    return selection_;
}

void SceneManager::setMode(const ToolbarMode mode) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            currentMode_ = visibleAreaMode_;
            break;

        case ToolbarMode::LINE:
            currentMode_ = &lineMode_;
            break;

        case ToolbarMode::ARROW:
            currentMode_ = &arrowMode_;
            break;

        case ToolbarMode::RECT:
            currentMode_ = &rectMode_;
            break;

        case ToolbarMode::ELLIPSE:
            currentMode_ = &ellipseMode_;
            break;

        case ToolbarMode::TEXT:
            currentMode_ = &textMode_;
            break;
    }

    emit modeChanged(mode);
}

AbstractMode* SceneManager::mode() const {
    return currentMode_;
}

VisibleAreaMode* SceneManager::visibleAreaMode() {
    return visibleAreaMode_;
}

LineMode& SceneManager::lineMode() {
    return lineMode_;
}

ArrowMode& SceneManager::arrowMode() {
    return arrowMode_;
}

RectMode& SceneManager::rectMode() {
    return rectMode_;
}

EllipseMode& SceneManager::ellipseMode() {
    return ellipseMode_;
}

TextMode& SceneManager::textMode() {
    return textMode_;
}

void SceneManager::reinitVisibleArea() {
    if (0 != visibleAreaMode_) {
        delete visibleAreaMode_;
    }

    QDesktopWidget* desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    visibleAreaMode_ = new VisibleAreaMode(scene_, appView_.toolbar() , geo.width(), geo.height());
    visibleAreaMode_->move(QCursor::pos().x(), QCursor::pos().y());

    currentMode_ = visibleAreaMode_;
    scene_.setMode(ToolbarMode::VISIBLE_AREA);
    appView_.toolbar().select(ToolbarMode::VISIBLE_AREA);
}

void SceneManager::selectItem() {
    QList<QGraphicsItem*> items = scene_.selectedItems();

    if (!items.empty()) {
        QGraphicsItem* firstItem = items.first();

        if (items.size() == 1) {
            if (firstItem != selection_) {
                selection_ = firstItem;
            }
        } else {
            QGraphicsItem* tmpItem = selection_;
            selection_ = firstItem;
            tmpItem->setSelected(false);
        }
    }
}
