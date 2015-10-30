#include <QApplication>
#include <QClipboard>
#include "App.h"

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
