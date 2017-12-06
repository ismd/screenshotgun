#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "App.h"
#include "Overlay.h"

Overlay::Overlay(App& app)
    : app_(app),
      overlayView_(this, *this),
      toolbar_(this, *this) {

    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::BypassWindowManagerHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::WindowOverridesSystemGestures);
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::BlankCursor);
    
#ifdef Q_OS_MACOS
    setAttribute(Qt::WA_MacAlwaysShowToolWindow);
#endif
}

App& Overlay::app() const {
    return app_;
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

void Overlay::hideEvent(QHideEvent* e) {
    toolbar_.hide();
}