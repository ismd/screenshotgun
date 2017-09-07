#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "App.h"
#include "Overlay.h"

Overlay::Overlay(App& app)
    : app_(app),
      toolbar_(*this),
      visibleAreaMode_(0),
      lineMode_(scene_),
      arrowMode_(scene_),
      rectMode_(scene_),
      ellipseMode_(scene_),
      textMode_(scene_, *this),
      usingMode_(false) {

    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::BypassWindowManagerHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::WindowOverridesSystemGestures);

    setFocusPolicy(Qt::StrongFocus);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setMouseTracking(true);
    setCursor(Qt::BlankCursor);

    setScene(&scene_);
}

Overlay::~Overlay() {
    delete visibleAreaMode_;
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
    scene_.setSceneRect(0, 0, width, height);

    reinitVisibleArea();

    // Background screenshot
    scene_.addPixmap(screenshot_);

    //setGeometry(0, 0, width, height);
    raise();
    repaint();
    activateWindow();
    showNormal();
}

QGraphicsScene& Overlay::scene() {
    return scene_;
}

VisibleAreaMode& Overlay::visibleAreaMode() const {
    return *visibleAreaMode_;
}

void Overlay::setMode(const ToolbarMode mode) {
    emit toolChanged(mode);

    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            currentMode_ = visibleAreaMode_;
            break;

        case ToolbarMode::LINE:
            currentMode_ = &lineMode_;
            app().history().setLastTool(ToolbarMode::LINE);
            break;

        case ToolbarMode::ARROW:
            currentMode_ = &arrowMode_;
            app().history().setLastTool(ToolbarMode::ARROW);
            break;

        case ToolbarMode::RECT:
            currentMode_ = &rectMode_;
            app().history().setLastTool(ToolbarMode::RECT);
            break;

        case ToolbarMode::ELLIPSE:
            currentMode_ = &ellipseMode_;
            app().history().setLastTool(ToolbarMode::ELLIPSE);
            break;

        case ToolbarMode::TEXT:
            currentMode_ = &textMode_;
            app().history().setLastTool(ToolbarMode::TEXT);
            break;
    }
}

void Overlay::reinitVisibleArea() {
    if (0 != visibleAreaMode_) {
        delete visibleAreaMode_;
    }

    QDesktopWidget* desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    visibleAreaMode_ = new VisibleAreaMode(scene_, toolbar_ , geo.width(), geo.height());
    currentMode_ = visibleAreaMode_;
    toolbar_.select(ToolbarMode::VISIBLE_AREA);
}

Toolbar& Overlay::toolbar() {
    return toolbar_;
}

void Overlay::mousePressEvent(QMouseEvent* e) {
    int x = e->x();
    int y = e->y();

    if (currentMode_ != visibleAreaMode_
        && visibleAreaMode_->initialized()
        && visibleAreaMode_->isResizablePosition(x, y))
    {
        visibleAreaMode_->resizeInit(x, y);
        return;
    }

    usingMode_ = true;
    currentMode_->init(x, y);
}

void Overlay::mouseMoveEvent(QMouseEvent* e) {
    int x = e->x();
    int y = e->y();

    if (visibleAreaMode_->resizing()) {
        visibleAreaMode_->resizeMove(x, y);
    } else if (usingMode_ || currentMode_ == visibleAreaMode_ && !visibleAreaMode_->initialized()) {
        currentMode_->move(x, y);
    } else if (currentMode_ != visibleAreaMode_ && visibleAreaMode_->isResizablePosition(x, y)) {
        switch (visibleAreaMode_->resizablePosition(x, y)) {
            case ResizeDirection::TOP:
            case ResizeDirection::BOTTOM:
                setCursor(Qt::SizeVerCursor);
                break;

            case ResizeDirection::LEFT:
            case ResizeDirection::RIGHT:
                setCursor(Qt::SizeHorCursor);
                break;

            case ResizeDirection::TOP_LEFT:
            case ResizeDirection::BOTTOM_RIGHT:
                setCursor(Qt::SizeFDiagCursor);
                break;

            case ResizeDirection::TOP_RIGHT:
            case ResizeDirection::BOTTOM_LEFT:
                setCursor(Qt::SizeBDiagCursor);
                break;
        }
    } else if (currentMode_ == &textMode_) {
        setCursor(Qt::IBeamCursor);
    } else {
        setCursor(Qt::CrossCursor);
    }
}

void Overlay::mouseReleaseEvent(QMouseEvent* e) {
    int x = e->x();
    int y = e->y();

    if (visibleAreaMode_->resizing()) {
        visibleAreaMode_->resizeStop(x, y);
        return;
    }

    currentMode_->stop(x, y);

    if (currentMode_ != visibleAreaMode_) {
        usingMode_ = false;
    }
}

void Overlay::wheelEvent(QWheelEvent* e) {
    if (e->delta() < 0) {
        toolbar_.setSelectedNext();
    } else {
        toolbar_.setSelectedPrevious();
    }
}

void Overlay::keyReleaseEvent(QKeyEvent* e) {
    int key = e->key();

    if (key == Qt::Key_Escape) {
        hide();
        toolbar_.hide();
    } else if (key == Qt::Key_Return) {
        if (currentMode_ != &textMode_ || textMode_.textArea() == 0 || !textMode_.textArea()->hasFocus()) {
            app().setCopyImageToClipboard(e->modifiers().testFlag(Qt::AltModifier));
            toolbar_.submit();
        }
    }

    QGraphicsView::keyReleaseEvent(e);
}
