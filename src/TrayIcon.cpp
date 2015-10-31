#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include "App.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon(App& app)
    : app_(app),
      makeScreenshotAction_("Сделать скриншот", this),
      updateAction_("Обновить", this),
      settingsAction_("Настройки", this),
      quitAction_("Выход", this) {

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));

    connect(&makeScreenshotAction_, SIGNAL(triggered()),
            this, SLOT(makeScreenshotSlot()));

    connect(&updateAction_, SIGNAL(triggered()),
            this, SLOT(updateSlot()));

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
    bool result = QProcess::startDetached("maintenancetool.exe --updater");

    if (!result) {
        QMessageBox::critical(NULL,
                              "Не удалось запустить maintenancetool.exe",
                              "Скачайте инсталлятор с сайта http://screenshotgun.com и переустановите приложение.");
    }
}

void TrayIcon::showSettings() {
    app_.settingsForm().show();
}
