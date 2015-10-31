#include "App.h"
#include "Autostartup.h"
#include "SettingsForm.h"
#include "ui_Settings.h"

SettingsForm::SettingsForm(App& app) : ui(new Ui::Settings), app_(app), settings_(app_.settings()) {
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

    ui->autoStartupCheckBox->setChecked(settings_.autostartup());
    ui->serverEdit->setText(settings_.serverUrl());
}

SettingsForm::~SettingsForm() {
    delete ui;
}

bool SettingsForm::valid() {
    QString serverUrl = ui->serverEdit->text();
    bool valid = serverUrl.length() > 0;

    if (valid) {
        app_.server().setUrl(serverUrl);
        saveValues();
    }

    return valid;
}

void SettingsForm::error(const QString& message) {
    ui->errorLabel->setText(message);

    if ("" != message) {
        ui->errorLabel->setVisible(true);
        ui->submitButtons->setEnabled(true);
    } else {
        ui->errorLabel->setVisible(false);
        ui->submitButtons->setEnabled(false);
    }
}

void SettingsForm::show() {
    if ("" == ui->serverEdit->text()) {
        ui->serverEdit->setText("screenshotgun.com");
    }

    ui->submitButtons->setEnabled(true);
    QDialog::show();
}

void SettingsForm::accept() {
    error("");

    if (!valid()) {
        ui->submitButtons->setEnabled(true);
    }
}

void SettingsForm::saveValues() {
    bool autoStartupValue = ui->autoStartupCheckBox->isChecked();

    settings_.autostartup(autoStartupValue);
    settings_.serverUrl(ui->serverEdit->text());

    AutoStartup autoStartup;
    autoStartup.set(autoStartupValue);
}
