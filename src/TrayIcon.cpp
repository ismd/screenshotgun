#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include "App.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon(App& app)
    : app_(app),
      makeScreenshotAction_("Сделать скриншот", this),
      updateAction_("Обновить", this),
      settingsAction_("Настройки", this),
      historyMenu_("История"),
      quitAction_("Выход", this) {

#ifndef Q_OS_MACOS
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
#endif

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
#elif defined(Q_OS_MACOS)
    setIcon(QIcon(":/icons/icon-22.png"));
#endif

    setToolTip("Screenshotgun");

    iconMenu_.addAction(&makeScreenshotAction_);
#if defined(Q_OS_WIN32) || defined(Q_OS_MACOS)
    iconMenu_.addAction(&updateAction_);
#endif
    iconMenu_.addAction(&settingsAction_);
    iconMenu_.addMenu(&historyMenu_);
    iconMenu_.addAction(&quitAction_);

    setContextMenu(&iconMenu_);
}

void TrayIcon::show() {
    connect(&app_.history(), SIGNAL(linkAdded(const QString&)),
            this, SLOT(linkAdded(const QString&)));

    foreach (const QString& link, app_.history().links()) {
        linkAdded(link);
    }

    QSystemTrayIcon::show();
}

void TrayIcon::showMessage(const QString& title, const QString& msg, MessageIcon icon, int msecs) {
    disconnect(this, SIGNAL(messageClicked()),
               &app_.updater(), SLOT(show()));

#if defined(Q_OS_MACOS)
    if (canOsXSendUserNotification()) {
        sendOsXUserNotification(title, msg);
    }
#else
    QSystemTrayIcon::showMessage(title, msg, icon, msecs);
#endif
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
    app_.updater().check();
}

void TrayIcon::showSettings() {
    app_.settingsForm().show();
}

void TrayIcon::openLink() {
    QAction* action = static_cast<QAction*>(QObject::sender());
    QDesktopServices::openUrl(action->data().toString());
}

void TrayIcon::linkAdded(const QString& link) {
    QAction* action = new QAction(link, this);
    action->setData(link);

    connect(action, SIGNAL(triggered()),
            this, SLOT(openLink()));

    QList<QAction*> actions = historyMenu_.actions();
    if (actions.empty()) {
        historyMenu_.addAction(action);
    } else {
        historyMenu_.insertAction(actions.first(), action);
    }

    if (actions.size() > 9) {
        historyMenu_.removeAction(actions.last());
    }
}
