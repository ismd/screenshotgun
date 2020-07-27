#include <QDialogButtonBox>
#include <QFileInfo>
#include <QMessageBox>
#include "App.h"
#include "Updater.h"

Updater::Updater(App& app) : ui(new Ui::Update), app_(app) {
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Обновить");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");

#if defined(Q_OS_MACOS)
    maintenancetool_ = QFileInfo(QCoreApplication::applicationDirPath()
                                 + "/../../maintenancetool.app/Contents/MacOS/maintenancetool").absoluteFilePath();
#endif

    connect(&process_, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(checkUpdates()));

    connect(&process_, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(errorOccurred(QProcess::ProcessError)));
}

Updater::~Updater() {
    delete ui;
}

void Updater::check() {
#if defined(Q_OS_WIN32) || defined(Q_OS_MACOS)
    qInfo() << "Running:" << maintenancetool_ << "--checkupdates";
    process_.start(maintenancetool_ + " --checkupdates");
#endif
}

void Updater::checkUpdates() {
    QString output = process_.readAllStandardOutput();

    QRegExp rx("<update.+version=\"(.+)\"");
    rx.setMinimal(true);

    if (-1 != rx.indexIn(output)) {
        QString version = rx.cap(1);
        qInfo() << "Update available:" << version;

        connect(&app_.trayIcon(), SIGNAL(messageClicked()),
                this, SLOT(show()));

        app_.trayIcon().showMessage("Screenshotgun", "Доступна версия " + version);
        ui->label->setText("Доступна версия " + version);
        show();
    } else {
        qInfo() << "No updates available";
        app_.trayIcon().showMessage("Screenshotgun",
                                    "Нет доступных обновлений",
                                    QSystemTrayIcon::Information,
                                    3000);
    }
}

void Updater::accept() {
    ui->buttonBox->setEnabled(false);
    bool result = QProcess::startDetached(maintenancetool_, {"--updater"});

    if (!result) {
        QMessageBox::critical(NULL,
                              "Не удалось запустить maintenancetool.exe",
                              "Скачайте инсталлятор с сайта http://screenshotgun.com и переустановите приложение.");
        ui->buttonBox->setEnabled(true);
        return;
    }

    qApp->quit();
}

void Updater::errorOccurred(QProcess::ProcessError error) {
    qDebug() << "Can't run maintenancetool: " << error;
}
