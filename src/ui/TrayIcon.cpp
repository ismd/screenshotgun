#include "TrayIcon.h"
#include "src/Context.h"

#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>

TrayIcon::TrayIcon()
    : makeScreenshotAction_("Make screenshot"),
      updateAction_("Update"),
      settingsAction_("Settings"),
      historyMenu_("History"),
      quitAction_("Quit")
{
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

    for (const QString& url : Context::getInstance().history->linksFromHistory()) {
        addLinkToHistory(url);
    }

    connect(&makeScreenshotAction_, &QAction::triggered, this, [&]() {
        emit screenshotActionTriggered();
    });

    connect(&updateAction_, &QAction::triggered, this, [&]() {
        Context::getInstance().updater.check();
    });

    connect(&settingsAction_, &QAction::triggered, this, [&]() {
        Context::getInstance().settingsForm->show();
    });

    connect(&quitAction_, &QAction::triggered, qApp, &QCoreApplication::quit, Qt::QueuedConnection);

    connect(this, &QSystemTrayIcon::activated, this, [&](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            emit screenshotActionTriggered();
        }
    });

    connect(Context::getInstance().history, &History::linkAdded, this, [&](const QString& url) {
        addLinkToHistory(url);
    });
}

void TrayIcon::addLinkToHistory(const QString& link) {
    QAction* action = new QAction(link);
    action->setData(link);

    connect(action, &QAction::triggered, this, [&]() {
        QAction* action = static_cast<QAction*>(QObject::sender());
        QDesktopServices::openUrl(action->data().toString());
    });

    QList<QAction*> actions = historyMenu_.actions();
    if (actions.empty()) {
        historyMenu_.addAction(action);
    } else {
        historyMenu_.insertAction(actions.first(), action);
    }

    if (actions.size() > 4) {
        QAction* action = actions.last();
        historyMenu_.removeAction(action);
        action->deleteLater();
    }
}
