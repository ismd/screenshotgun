#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include "App.h"

App::App()
    : overlay_(*this),
      trayIcon_(*this),
      settingsForm_(*this),
      google_(*this),
      copyImageToClipboard_(false),
      connectionChecks_(0),
      connected_(false) {
    connect(&server_, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));

    connect(&server_, SIGNAL(connectionError()),
            this, SLOT(connectionError()));

    connect(&server_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&server_, SIGNAL(uploadError()),
            this, SLOT(uploadError()));

    connect(&dropbox_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&dropbox_, SIGNAL(uploadError(QString)),
            this, SLOT(uploadError(QString)));

    connect(&yandex_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&yandex_, SIGNAL(uploadError(QString)),
            this, SLOT(uploadError(QString)));

    connect(&google_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&google_, SIGNAL(uploadError(QString)),
            this, SLOT(uploadError(QString)));

    initShortcut();
    connect(&trayIcon_, SIGNAL(makeScreenshot()),
            this, SLOT(makeScreenshot()));

    settingsForm_.init();
    if (!settingsForm_.valid(false)) {
        settingsForm_.show();
    }

    trayIcon_.show();

    connect(&updater_, SIGNAL(updateAvailable(QString)),
            this, SLOT(updateAvailable(const QString&)));

    updater_.check();
}

SettingsForm& App::settingsForm() {
    return settingsForm_;
}

UploadService App::uploadService() const {
    return service_;
}

Server& App::server() {
    return server_;
}

Dropbox& App::dropbox() {
    return dropbox_;
}

Yandex& App::yandex() {
    return yandex_;
}

Google& App::google() {
    return google_;
}

Settings& App::settings() {
    return settings_;
}

History& App::history() {
    return history_;
}

TrayIcon& App::trayIcon() {
    return trayIcon_;
}

Updater& App::updater() {
    return updater_;
}

void App::setUploadService(UploadService service) {
    service_ = service;
}

void App::setCopyImageToClipboard(bool value) {
    copyImageToClipboard_ = value;
}

void App::setConnectionChecks(int value) {
    connectionChecks_ = value;
}

bool App::connected() const {
    return connected_;
}

void App::timerEvent(QTimerEvent *event) {
    if (-1 != connectionChecks_) {
        server_.checkConnection();
    }

    if (-1 == connectionChecks_ || ++connectionChecks_ > 2) {
        killTimer(event->timerId());
        connectionChecks_ = -1;
    }
}

void App::makeScreenshot() {
    overlay_.makeScreenshot();
}

void App::connectionSuccess() {
    qDebug() << "Connection established to" << server_.url();

    connected_ = true;
    connectionChecks_ = -1;
    settingsForm_.hide();
}

void App::connectionError() {
    qDebug() << "Can't connect to" << server_.url() << "Attempt #" << connectionChecks_;

    if (0 == connectionChecks_) {
        startTimer(20000);
    } else if (-1 == connectionChecks_) {
        settingsForm_.showCantConnect();
    }
}

void App::uploadSuccess(const QString& url) {
    lastUrl_ = url;
    QClipboard* clipboard = QApplication::clipboard();
    history_.addLink(url);

    if (copyImageToClipboard_) {
        clipboard->setImage(overlay_.toolbar().image());

        trayIcon_.showMessage("Изображение скопировано в буфер обмена",
                              url,
                              QSystemTrayIcon::Information,
                              3000);
    } else {
        clipboard->setText(url);

        trayIcon_.showMessage("Ссылка скопирована в буфер обмена",
                              url,
                              QSystemTrayIcon::Information,
                              3000);
    }

    disconnect(&trayIcon_, SIGNAL(messageClicked()),
               this, SLOT(openUrl()));

    connect(&trayIcon_, SIGNAL(messageClicked()),
            this, SLOT(openUrl()));
}

void App::uploadError() {
    uploadError("Проверьте логи на сервере");
}

void App::uploadError(QString error) {
    trayIcon_.showError("Ошибка во время загрузки скриншота", error);
}

void App::updateAvailable(const QString& version) {
    trayIcon_.showNewVersionAvailable(version);
}

void App::openUrl() {
    QDesktopServices::openUrl(QUrl(lastUrl_));
}

void App::initShortcut() {
#if defined(Q_OS_LINUX)
    shortcut_.setShortcut(QKeySequence(tr("Alt+Print")));

    connect(&shortcut_, SIGNAL(activated()),
            &overlay_, SLOT(makeScreenshot()));
#elif defined(Q_OS_WIN32)
    RegisterHotKey((HWND)overlay_.winId(), 100, MOD_ALT, VK_SNAPSHOT);
#endif
}

#ifdef Q_OS_WIN32
bool App::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    MSG* msg = reinterpret_cast<MSG*>(message);

    if (msg->message == WM_HOTKEY) {
        if (msg->wParam == 100) {
            overlay_.makeScreenshot();
            return true;
        }
    }

    return false;
}
#endif
