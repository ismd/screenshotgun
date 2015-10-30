#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "App.h"
#include "AppView.h"

AppView::AppView(App& app)
    : app_(app),
      toolbar_(*this),
      visibleAreaMode_(0),
      lineMode_(scene_),
      arrowMode_(scene_),
      rectMode_(scene_),
      currentMode_(visibleAreaMode_) {

    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    reinitVisibleArea();
    setScene(&scene_);

#if defined(Q_OS_LINUX)
    shortcut_.setShortcut(QKeySequence(tr("Alt+Print")));

    connect(&shortcut_, SIGNAL(activated()),
            this, SLOT(makeScreenshot()));
#elif defined(Q_OS_WIN32)
    RegisterHotKey((HWND)winId(), 100, MOD_ALT, VK_SNAPSHOT);
#endif
}

AppView::~AppView() {
    delete visibleAreaMode_;
}

App& AppView::app() {
    return app_;
}

void AppView::makeScreenshot() {
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
    scene_.clear();
    scene_.setSceneRect(0, 0, width, height);
    reinitVisibleArea();

    // Background screenshot
    scene_.addPixmap(screenshot_);
    showFullScreen();
}

QGraphicsScene& AppView::scene() {
    return scene_;
}

VisibleAreaMode& AppView::visibleAreaMode() {
    return *visibleAreaMode_;
}

void AppView::mode(ToolbarMode mode) {
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
    }
}

void AppView::reinitVisibleArea() {
    if (visibleAreaMode_ != 0) {
        delete visibleAreaMode_;
    }

    visibleAreaMode_ = new VisibleAreaMode(scene_, toolbar_);
    currentMode_ = visibleAreaMode_;

    toolbar_.select(ToolbarMode::VISIBLE_AREA);
}

void AppView::mousePressEvent(QMouseEvent* e) {
    currentMode_->init(e->x(), e->y());
}

void AppView::mouseMoveEvent(QMouseEvent* e) {
    currentMode_->move(e->x(), e->y());
}

void AppView::mouseReleaseEvent(QMouseEvent* e) {
    currentMode_->stop(e->x(), e->y());
}

void AppView::wheelEvent(QWheelEvent* e) {
    if (e->delta() < 0) {
        toolbar_.setSelectedNext();
    } else {
        toolbar_.setSelectedPrevious();
    }
}

void AppView::keyReleaseEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        hide();
        toolbar_.hide();
    }
}

#ifdef Q_OS_WIN32
bool AppView::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    MSG* msg = reinterpret_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY){
        if (msg->wParam == 100){
            makeScreenshot();
            return true;
        }
    }

    return false;
}
#endif
