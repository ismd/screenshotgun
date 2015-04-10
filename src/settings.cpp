#include "settings.h"
#include "ui_settings.h"
#include "autostartup.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    _settings(new QSettings("screenshotgun"))
{
    ui->setupUi(this);

    ui->autoStartupCheckBox->setChecked(_settings->value("common/autostartup").toBool());
    ui->serverRadioButton->setChecked(_settings->value("server/checked").toBool());
    ui->serverEdit->setText(_settings->value("server/url").toString());
    ui->errorLabel->setVisible(false);
}

Settings::~Settings()
{
    delete ui;
}

bool Settings::isValid()
{
    bool isValid = ui->serverEdit->text().length() > 0;

    if (isValid) {
        bool autoStartup = ui->autoStartupCheckBox->isChecked();

        _settings->setValue("common/autostartup", autoStartup);
        _settings->setValue("server/checked", ui->serverRadioButton->isChecked());
        _settings->setValue("server/url", ui->serverEdit->text());

        AutoStartup as;
        as.set(autoStartup);

        emit(valid());
    }

    return isValid;
}

QString Settings::server()
{
    return _settings->value("server/url").toString();
}

void Settings::accept()
{
    ui->submitButtons->setEnabled(false);

    if (!isValid()) {
        ui->submitButtons->setEnabled(true);
    }
}

Settings* Settings::setError(QString message)
{
    ui->errorLabel->setText(message);
    ui->errorLabel->setVisible("" == message ? false : true);

    if ("" != message) {
        ui->submitButtons->setEnabled(true);
    }

    return this;
}
