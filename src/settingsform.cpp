#include "autostartup.h"
#include "settingsform.h"
#include "ui_settings.h"

SettingsForm::SettingsForm(Settings* settings, QWidget *parent) :
    _settings(settings),
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

    if (!_settings->exists()) {
        return;
    }

    ui->autoStartupCheckBox->setChecked(_settings->autostartup());
    ui->serverRadioButton->setChecked(_settings->serverChecked());

    QString url(_settings->serverUrl());
    if (url.length() > 0) {
        ui->serverEdit->setText(url);
    }
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

bool SettingsForm::isValid()
{
    bool isValid = ui->serverEdit->text().length() > 0;

    if (isValid) {
        bool autoStartup = ui->autoStartupCheckBox->isChecked();

        _settings->setAutostartup(autoStartup);
        _settings->setServerChecked(ui->serverRadioButton->isChecked());
        _settings->setServerUrl(ui->serverEdit->text());

        AutoStartup as;
        as.set(autoStartup);

        emit(valid());
    }

    return isValid;
}

QString SettingsForm::server()
{
    return _settings->serverUrl();
}

void SettingsForm::accept()
{
    ui->submitButtons->setEnabled(false);

    if (!isValid()) {
        ui->submitButtons->setEnabled(true);
    }
}

SettingsForm* SettingsForm::setError(QString message)
{
    ui->errorLabel->setText(message);
    ui->errorLabel->setVisible("" == message ? false : true);

    if ("" != message) {
        ui->submitButtons->setEnabled(true);
    }

    return this;
}

void SettingsForm::show()
{
    ui->submitButtons->setEnabled(true);
    QDialog::show();
}
