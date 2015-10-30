#include <QApplication>
#include "App.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon(App& app)
    : app_(app),
      makeScreenshotAction_("Сделать скриншот", this),
      settingsAction_("Настройки", this),
      quitAction_("Выход", this) {

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));

    connect(&makeScreenshotAction_, SIGNAL(triggered()),
            this, SLOT(makeScreenshotSlot()));

    connect(&settingsAction_, SIGNAL(triggered()),
            this, SLOT(showSettings()));

    connect(&quitAction_, SIGNAL(triggered()),
            qApp, SLOT(quit()));

#ifdef Q_OS_WIN32
    setIcon(QIcon(":/icons/icon-16.png"));
#elif defined(Q_OS_LINUX)
    setIcon(QIcon(":/icons/icon-22.png"));
#endif

    setToolTip("Screenshotgun");

    iconMenu_.addAction(&makeScreenshotAction_);
    iconMenu_.addAction(&settingsAction_);
    iconMenu_.addAction(&quitAction_);

    setContextMenu(&iconMenu_);
}

void TrayIcon::trayActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        makeScreenshotSlot();
    }
}

void TrayIcon::makeScreenshotSlot() {
    emit makeScreenshot();
}

void TrayIcon::showSettings() {
    app_.settingsForm().show();
}
