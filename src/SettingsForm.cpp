#include "App.h"
#include "Autostartup.h"
#include "SettingsForm.h"

SettingsForm::SettingsForm(App& app) : ui(new Ui::Settings), app_(app), settings_(app.settings()) {
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
}

SettingsForm::~SettingsForm() {
    delete ui;
}

void SettingsForm::init() {
    ui->autoStartupCheckBox->setChecked(settings_.autostartup());
    ui->serverEdit->setText(settings_.serverUrl());
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

void SettingsForm::showCantConnect() {
    app_.setConnectionChecks(-1);
    error("Не удалось подключиться к серверу");
    show();
}

void SettingsForm::accept() {
    error("");
    app_.setConnectionChecks(-1);

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
