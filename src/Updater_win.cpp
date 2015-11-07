#include <QDialogButtonBox>
#include <QMessageBox>
#include <QRegExp>
#include "App.h"
#include "Updater_win.h"

Updater::Updater() : ui(new Ui::Update) {
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Обновить");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");

    connect(&process_, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(checkUpdates()));
}

Updater::~Updater() {
    delete ui;
}

void Updater::check() {
    process_.start("maintenancetool.exe --checkupdates");
}

void Updater::checkUpdates() {
    QString output = process_.readAllStandardOutput();

    QRegExp rx("<update.+version=\"(.+)\"");
    rx.setMinimal(true);

    if (-1 != rx.indexIn(output)) {
        ui->label->setText("Доступна версия " + rx.cap(1));
        show();
    } else {
        emit noUpdate();
    }
}

void Updater::accept() {
    ui->buttonBox->setEnabled(false);
    bool result = QProcess::startDetached("maintenancetool.exe --updater");

    if (!result) {
        QMessageBox::critical(NULL,
                              "Не удалось запустить maintenancetool.exe",
                              "Скачайте инсталлятор с сайта http://screenshotgun.com и переустановите приложение.");
        ui->buttonBox->setEnabled(true);
        return;
    }

    qApp->quit();
}
