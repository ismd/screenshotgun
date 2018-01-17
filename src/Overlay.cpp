#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "App.h"
#include "Overlay.h"

Overlay::Overlay(App& app)
    : app_(app),
      overlayView_(this, *this),
      toolbar_(this, *this),
      cursorLocked_(false) {

    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::BypassWindowManagerHint |
                   Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::WindowOverridesSystemGestures);

    setWindowModality(Qt::ApplicationModal);
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::BlankCursor);
    
#ifdef Q_OS_MACOS
    setAttribute(Qt::WA_MacAlwaysShowToolWindow);
#endif
}

App& Overlay::app() const {
    return app_;
}

OverlayView& Overlay::overlayView() {
    return overlayView_;
}

void Overlay::makeScreenshot() {
    if (app_.uploadService() == UploadService::SERVER && !app_.connected()) {
        app_.settingsForm().showCantConnect();
        return;
    }

    // Making screenshot
    QDesktopWidget* desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    screenshot_ = QGuiApplication::primaryScreen()->grabWindow(desktop->winId(),
                                                               geo.left(),
                                                               geo.top(),
                                                               geo.width(),
                                                               geo.height());

    int width = screenshot_.width(),
        height = screenshot_.height();

    setGeometry(0, 0, width, height);
    overlayView_.scene().setSceneRect(0, 0, width, height);

    reinitVisibleArea();

    // Background screenshot
    overlayView_.scene().addPixmap(screenshot_);

    setGeometry(0, 0, width, height);
    show();

    overlayView_.activateWindow();
    overlayView_.setFocus();
}

QGraphicsScene& Overlay::scene() {
    return overlayView_.scene();
}

VisibleAreaMode& Overlay::visibleAreaMode() const {
    return overlayView_.visibleAreaMode();
}

void Overlay::setMode(const ToolbarMode mode) {
    emit toolChanged(mode);
    overlayView_.setMode(mode);
}

void Overlay::reinitVisibleArea() {
    overlayView_.reinitVisibleArea();
}

Toolbar& Overlay::toolbar() {
    return toolbar_;
}

void Overlay::setCursor(const QCursor& cursor) {
    if (!cursorLocked_) {
        QWidget::setCursor(cursor);
    }
}

void Overlay::setCursorLocked(bool value) {
    cursorLocked_ = value;
}

void Overlay::addItem(AbstractItem* item) {
    items_.append(item);

    for (auto item : item->graphicItems()) {
        scene().addItem(item);
    }
}

void Overlay::hideEvent(QHideEvent* e) {
    toolbar_.hide();

    for (auto item : items_) {
        delete item;
    }

    items_.clear();

    Q_UNUSED(e);
}
