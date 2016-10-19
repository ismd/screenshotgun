#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include "App.h"

App::App()
    : appView_(*this),
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

    appView_.initShortcut();
    connect(&trayIcon_, SIGNAL(makeScreenshot()),
            this, SLOT(makeScreenshot()));

    settingsForm_.init();
    if (!settingsForm_.valid()) {
        settingsForm_.show();
    }

    trayIcon_.show();

#if defined(Q_OS_WIN32)
    connect(&updater_, SIGNAL(updateAvailable(QString)),
            this, SLOT(updateAvailable(const QString&)));

    updater_.check();
#endif
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

#if defined(Q_OS_WIN32)
Updater& App::updater() {
    return updater_;
}
#endif

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
    appView_.makeScreenshot();
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
        clipboard->setImage(appView_.toolbar().image());

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
#if defined(Q_OS_WIN32)
    trayIcon_.showNewVersionAvailable(version);
#endif
}

void App::openUrl() {
    QDesktopServices::openUrl(QUrl(lastUrl_));
}
