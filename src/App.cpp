#include <QApplication>
#include <QClipboard>
#include "App.h"

App::App() : appView_(*this), trayIcon_(*this), settingsForm_(*this) {
    connect(&server_, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));

    connect(&server_, SIGNAL(connectionError()),
            this, SLOT(connectionError()));

    connect(&server_, SIGNAL(uploadSuccess(QString)),
            this, SLOT(uploadSuccess(QString)));

    connect(&server_, SIGNAL(uploadError()),
            this, SLOT(uploadError()));

    settingsForm_.init();
    if (!settingsForm_.valid()) {
        settingsForm_.show();
    }

    trayIcon_.show();

#if defined(Q_OS_WIN32)
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

#if defined(Q_OS_WIN32)
Updater& App::updater() {
    return updater_;
}
#endif

void App::makeScreenshot() {
    appView_.makeScreenshot();
}

void App::connectionSuccess() {
    settingsForm_.hide();

    appView_.initShortcut();
    connect(&trayIcon_, SIGNAL(makeScreenshot()),
            this, SLOT(makeScreenshot()));
}

void App::connectionError() {
    settingsForm_.error("Не удалось подключиться к серверу");
    settingsForm_.show();
}

void App::uploadSuccess(QString url) {
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(url);

    trayIcon_.showMessage("Ссылка скопирована в буфер обмена",
                          url,
                          QSystemTrayIcon::Information,
                          3000);
}

void App::uploadError() {
    trayIcon_.showMessage("Ошибка во время загрузки скриншота",
                          "Обратитесь к разработчику и проверьте логи на сервере",
                          QSystemTrayIcon::Critical,
                          10000);
}
