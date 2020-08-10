#include "App.h"
#include "Context.h"

#include <QDesktopWidget>
#include <QScreen>

App::App() {
    Context& ctx = Context::getInstance();

    ctx.app = this;
    ctx.overlayView = new OverlayView();
    ctx.itemManager = new ItemManager();
    ctx.toolbar = new Toolbar(ctx.overlayView);
    ctx.settings = new Settings();
    ctx.settingsForm = new SettingsForm();
    ctx.dropbox = new Dropbox();
    ctx.google = new Google();
    ctx.server = new Server();
    ctx.yandex = new Yandex();
    ctx.clipboard = new Clipboard();
    ctx.history = new History();
    ctx.trayIcon = new TrayIcon();

    connect(ctx.trayIcon, &TrayIcon::screenshotActionTriggered, this, &App::makeScreenshot);
    connect(ctx.toolbar, &Toolbar::screenshotButtonClicked, this, &App::processScreenshot);
    connect(ctx.overlayView, &OverlayView::enterClicked, this, &App::processScreenshot);
    connect(ctx.overlayView, &OverlayView::escapeClicked, this, &App::cancelScreenshot);
    connect(this, &App::screenshotFinished, this, [&]() {
        delete pixmap;
    });
    connect(ctx.settingsForm, &SettingsForm::hotkeyChanged, this, [&](const QKeySequence seq) {
        initShortcut(seq);
        ctx.settings->setHotkey(seq);
    });

    ctx.itemManager->visibleAreaItem.addToScene();

    // Hotkey
    const QKeySequence seq = ctx.settings->hotkey();
    initShortcut(seq);
    ctx.settingsForm->setHotkey(seq);

#if defined(Q_OS_LINUX)
    connect(&shortcut_, &QxtGlobalShortcut::activated, this, &App::makeScreenshot);
#endif

    if (ctx.settingsForm->check()) {
        ctx.settingsForm->saveValues();
    } else {
        ctx.settingsForm->show();
    }

    ctx.trayIcon->show();
    // FIXME
    // ctx.updater.check();
}

void App::makeScreenshot() {
    Context& ctx = Context::getInstance();

    if (ctx.settings->service() == UploadService::SERVER && !ctx.server->connected()) {
        ctx.settingsForm->setError("Can't connect to server");
        ctx.settingsForm->show();
        return;
    }

    // Making screenshot
    const QDesktopWidget* desktop = QApplication::desktop();
    const QPoint pos = QCursor::pos();
    QScreen* screen = QGuiApplication::screenAt(pos);
    const QRect geo = screen->geometry();

    const QPixmap screenshot = screen->grabWindow(desktop->winId(),
        geo.left(),
        geo.top(),
        geo.width(),
        geo.height());

    const int width = screenshot.width(),
        height = screenshot.height();

    ctx.overlayView->setGeometry(geo);
    ctx.overlayView->scene.setSceneRect(0, 0, width, height);

    // Background screenshot
    pixmap = ctx.overlayView->scene.addPixmap(screenshot);
    ctx.itemManager->visibleAreaItem.move(pos.x() - geo.x(), pos.y() - geo.y());

    ctx.overlayView->activateWindow();
    ctx.overlayView->setFocus();
    ctx.overlayView->showFullScreen();
}

void App::processScreenshot() {
    Context& ctx = Context::getInstance();
    const VisibleAreaItem& visibleAreaItem = ctx.itemManager->visibleAreaItem;

    ctx.overlayView->scene.setSceneRect(visibleAreaItem.area.x,
        visibleAreaItem.area.y,
        visibleAreaItem.area.width,
        visibleAreaItem.area.height);

    QImage image(ctx.overlayView->scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ctx.overlayView->scene.render(&painter);

    switch (ctx.settings->service()) {
        case UploadService::SERVER:
            ctx.server->upload(image);
            break;

        case UploadService::DROPBOX:
            ctx.dropbox->upload(image);
            break;

        case UploadService::YANDEX:
            ctx.yandex->upload(image);
            break;

        case UploadService::GOOGLE:
            ctx.google->upload(image);
            break;

        case UploadService::CLIPBOARD:
            ctx.clipboard->upload(image);
            break;
    }

    emit screenshotFinished(true);
}

void App::cancelScreenshot() {
    emit screenshotFinished(false);
}

void App::initShortcut(const QKeySequence seq) {
#if defined(Q_OS_LINUX)
    initShortcutLinux(seq);
#endif

#if defined(Q_OS_WIN32)
    // FIXME
    // initShortcutWindows();
#endif
}

#if defined(Q_OS_LINUX)
void App::initShortcutLinux(const QKeySequence seq) {
    shortcut_.setShortcut(seq);
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
