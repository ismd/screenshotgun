#include <QApplication>
#include <QClipboard>
#include "App.h"

#ifdef Q_OS_WIN32
    #include <windows.h>
#endif

App::App() : appView_(*this), trayIcon_(*this), settingsForm_(*this) {
    connect(&server_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&server_, SIGNAL(uploadError()),
            this, SLOT(uploadError()));

    connect(&trayIcon_, SIGNAL(makeScreenshot()),
            this, SLOT(makeScreenshot()));

    if (!settingsForm_.valid()) {
        settingsForm_.show();
    }

    trayIcon_.show();

#ifdef Q_OS_WIN32
    RegisterHotKey((HWND)winId(), 100, MOD_ALT, VK_SNAPSHOT);
#elif defined(Q_OS_LINUX)
    shortcut_.setShortcut(QKeySequence(tr("Alt+Print")));

    connect(&shortcut_, SIGNAL(activated()),
            this, SLOT(makeScreenshot()));
#endif
}

SettingsForm& App::settingsForm() {
    return settingsForm_;
}

Server& App::server() {
    return server_;
}

void App::makeScreenshot() {
    appView_.makeScreenshot();
}

void App::uploadSuccess(QString url) {
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(url);

    trayIcon_.showMessage("Link copied to clipboard",
                          url,
                          QSystemTrayIcon::Information,
                          3000);
}

void App::uploadError() {
    trayIcon_.showMessage("Error while uploading screenshot",
                          "Check your server logs",
                          QSystemTrayIcon::Critical,
                          10000);
}

#ifdef Q_OS_WIN32
bool App::nativeEvent(const QByteArray& eventType, void* message, long* result) {
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
