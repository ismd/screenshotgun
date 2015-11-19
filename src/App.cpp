#include <QApplication>
#include <QClipboard>
#include "App.h"

App::App()
    : appView_(*this),
      trayIcon_(*this),
      settingsForm_(*this),
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

Server& App::server() {
    return server_;
}

Settings& App::settings() {
    return settings_;
}

History& App::history() {
    return history_;
}

#if defined(Q_OS_WIN32)
Updater& App::updater() {
    return updater_;
}
#endif

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
}

void App::uploadError() {
    trayIcon_.showError("Ошибка во время загрузки скриншота",
                        "Обратитесь к разработчику и проверьте логи на сервере");
}

void App::updateAvailable(const QString& version) {
#if defined(Q_OS_WIN32)
    trayIcon_.showNewVersionAvailable(version);
#endif
}
