#include "App.h"
#include "Context.h"

#include <QDesktopWidget>
#include <QScreen>

App::App() {
    Context& ctx = Context::getInstance();

    connect(&ctx.trayIcon, &TrayIcon::screenshotActionTriggered, this, &App::makeScreenshot);
    connect(&ctx.overlayView, &OverlayView::enterClicked, this, &App::makeScreenshot);

    if (ctx.settingsForm.check()) {
        ctx.settingsForm.saveValues();
    } else {
        ctx.settingsForm.show();
    }

    ctx.trayIcon.show();
    // ctx.updater.check();

#if defined(Q_OS_LINUX)
    // initShortcutLinux();
#endif

#if defined(Q_OS_WIN32)
    // initShortcutWindows();
#endif
}

void App::makeScreenshot() {
    Context& ctx = Context::getInstance();

    if (ctx.settings.service() == UploadService::SERVER && !ctx.server.connected()) {
        ctx.settingsForm.setError("Can't connect to server");
        ctx.settingsForm.show();
        return;
    }

    // Making screenshot
    QDesktopWidget* desktop = QApplication::desktop();
    QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
    QRect geo = screen->geometry();

    const QPixmap screenshot = screen->grabWindow(desktop->winId(),
        geo.left(),
        geo.top(),
        geo.width(),
        geo.height());

    int width = screenshot.width(),
        height = screenshot.height();

    ctx.overlayView.setGeometry(geo);
    ctx.overlayView.scene.setSceneRect(0, 0, width, height);

    // Background screenshot
    ctx.overlayView.scene.addPixmap(screenshot);
    ctx.overlayView.show();

    ctx.overlayView.activateWindow();
    ctx.overlayView.setFocus();
    ctx.overlayView.showFullScreen();
}

#if defined(Q_OS_LINUX)
void App::initShortcutLinux() {
    shortcut_.setShortcut(QKeySequence(tr("Alt+Print")));

    connect(&shortcut_, &QxtGlobalShortcut::activated, this, &App::makeScreenshot);
}
#endif

#if defined(Q_OS_WIN32)
void App::initShortcutWindows() {
    RegisterHotKey((HWND)overlay_.winId(), 100, MOD_ALT, VK_SNAPSHOT);
}

bool App::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    MSG* msg = reinterpret_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY) {
        if (msg->wParam == 100) {
            makeScreenshot();
            return true;
        }
    }

    return false;
}
#endif
