#include <QApplication>
#include <QMessageBox>
#include "App.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon(App& app)
    : app_(app),
      makeScreenshotAction_("Сделать скриншот", this),
#if defined(Q_OS_WIN32)
      updateAction_("Обновить", this),
#endif
      settingsAction_("Настройки", this),
      quitAction_("Выход", this) {

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));

    connect(&makeScreenshotAction_, SIGNAL(triggered()),
            this, SLOT(makeScreenshotSlot()));

#if defined(Q_OS_WIN32)
    connect(&updateAction_, SIGNAL(triggered()),
            this, SLOT(updateSlot()));
#endif

    connect(&settingsAction_, SIGNAL(triggered()),
            this, SLOT(showSettings()));

    connect(&quitAction_, SIGNAL(triggered()),
            qApp, SLOT(quit()));

#if defined(Q_OS_LINUX)
    setIcon(QIcon(":/icons/icon-22.png"));
#elif defined(Q_OS_WIN32)
    setIcon(QIcon(":/icons/icon-16.png"));
#endif

    setToolTip("Screenshotgun");

    iconMenu_.addAction(&makeScreenshotAction_);
#if defined(Q_OS_WIN32)
    iconMenu_.addAction(&updateAction_);
#endif
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

void TrayIcon::updateSlot() {
#if defined(Q_OS_WIN32)
    disconnect(&app_.updater(), SIGNAL(noUpdate()),
            this, SLOT(noUpdate()));
    connect(&app_.updater(), SIGNAL(noUpdate()),
            this, SLOT(noUpdate()));

    app_.updater().check();
#endif
}

void TrayIcon::noUpdate() {
#if defined(Q_OS_WIN32)
    showMessage("",
                "Нет доступных обновлений",
                QSystemTrayIcon::Information,
                3000);
#endif
}

void TrayIcon::showSettings() {
    app_.settingsForm().show();
}
