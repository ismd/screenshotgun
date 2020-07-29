#include "Updater.h"
#include "src/Context.h"

#include <QDialogButtonBox>
#include <QFileInfo>
#include <QMessageBox>

Updater::Updater() {
    ui.setupUi(this);

    ui.buttonBox->button(QDialogButtonBox::Ok)->setText("Update");
    ui.buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");

#if defined(Q_OS_MACOS)
    maintenancetool_ = QFileInfo(QCoreApplication::applicationDirPath()
        + "/../../maintenancetool.app/Contents/MacOS/maintenancetool").absoluteFilePath();
#endif

    connect(&process_, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(onCheckUpdates()));
    connect(&process_, &QProcess::errorOccurred, this, &Updater::onErrorOccurred);
}

void Updater::check() {
#if defined(Q_OS_WIN32) || defined(Q_OS_MACOS)
    qInfo() << "Running:" << maintenancetool_ << "--checkupdates";
    process_.start(maintenancetool_ + " --checkupdates");
#endif
}

void Updater::onCheckUpdates() {
    Context& ctx = Context::getInstance();
    QString output = process_.readAllStandardOutput();

    QRegExp rx("<update.+version=\"(.+)\"");
    rx.setMinimal(true);

    if (rx.indexIn(output) != -1) {
        QString version = rx.cap(1);
        qInfo() << "Update available:" << version;

        ctx.trayIcon.showMessage("Screenshotgun", "Version available " + version);
        ui.label->setText("New version available " + version);
        show();
    } else {
        qInfo() << "No updates available";
        ctx.trayIcon.showMessage("Screenshotgun",
            "No updates",
            QSystemTrayIcon::Information,
            3000);
    }
}

void Updater::accept() {
    ui.buttonBox->setEnabled(false);
    bool result = QProcess::startDetached(maintenancetool_, {"--updater"});

    if (!result) {
        QMessageBox::critical(
            nullptr,
            "Can't run maintenancetool",
            "Download the application from http://screenshotgun.com and reinstall",
            QMessageBox::Ok);

        ui.buttonBox->setEnabled(true);
        return;
    }

    qApp->quit();
}

void Updater::onErrorOccurred(QProcess::ProcessError error) {
    qDebug() << "Can't run maintenancetool: " << error;
}
