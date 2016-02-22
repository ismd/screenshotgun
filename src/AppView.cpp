#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "App.h"
#include "AppView.h"

AppView::AppView(App& app)
    : app_(app),
      sceneManager_(*this),
      toolbar_(*this) {

#ifndef Q_OS_OSX
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint |
                   Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
#else
    setWindowFlags(Qt::Drawer | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint |
                   Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
#endif

    setFocusPolicy(Qt::StrongFocus);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    setMouseTracking(true);
    setCursor(Qt::BlankCursor);
    setCacheMode(QGraphicsView::CacheBackground);

    setScene(&sceneManager_.scene());

    connect(&sceneManager_, SIGNAL(modeChanged(ToolbarMode)),
            &app_.history(), SLOT(setLastTool(ToolbarMode)));
}

AppView::~AppView() {
}

App& AppView::app() const {
    return app_;
}

void AppView::makeScreenshot() {
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
    sceneManager_.scene().setSceneRect(0, 0, width, height);

    sceneManager_.reinitVisibleArea();

    // Background screenshot
    setBackgroundBrush(screenshot_);

#ifndef Q_OS_OSX
    showFullScreen();
#else
    showMaximized();
#endif
}

SceneManager& AppView::sceneManager() {
    return sceneManager_;
}

Toolbar& AppView::toolbar() {
    return toolbar_;
}

void AppView::initShortcut() {
#if defined(Q_OS_LINUX)
    shortcut_.setShortcut(QKeySequence(tr("Alt+Print")));

    connect(&shortcut_, SIGNAL(activated()),
            this, SLOT(makeScreenshot()));
#elif defined(Q_OS_WIN32)
    RegisterHotKey((HWND)winId(), 100, MOD_ALT, VK_SNAPSHOT);
#endif
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
