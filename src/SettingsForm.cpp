#include "App.h"
#include "Autostartup.h"
#include "SettingsForm.h"

SettingsForm::SettingsForm(App& app)
        : ui(new Ui::Settings),
          app_(app),
          settings_(app.settings()),
          oauth_(app) {
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

    connect(ui->authDropbox, SIGNAL(clicked()),
            this, SLOT(showAuthDropbox()));

    connect(ui->authYandex, SIGNAL(clicked()),
            this, SLOT(showAuthYandex()));
}

SettingsForm::~SettingsForm() {
    delete ui;
}

void SettingsForm::init() {
    switch (settings_.service()) {
        case UploadService::SERVER:
            ui->radioButtonServer->setChecked(true);
            break;

        case UploadService::DROPBOX:
            ui->radioButtonDropbox->setChecked(true);
            break;

        case UploadService::YANDEX:
            ui->radioButtonYandex->setChecked(true);
            break;
    }

    ui->autoStartupCheckBox->setChecked(settings_.autostartup());
    ui->serverEdit->setText(settings_.serverUrl());
}

bool SettingsForm::valid() {
    bool valid = false;

    if (settings_.exists()) {
        if (ui->radioButtonServer->isChecked()) {
            valid = ui->serverEdit->text().length() > 0;

            if (valid) {
                app_.setUploadService(UploadService::SERVER);
                app_.server().setUrl(ui->serverEdit->text());
            } else {
                error("Не указан адрес сервера");
            }
        } else if (ui->radioButtonDropbox->isChecked()) {
            valid = settings_.dropboxToken().length() > 0;

            if (valid) {
                hide();
                app_.setUploadService(UploadService::DROPBOX);
                app_.dropbox().setToken(settings_.dropboxToken());
            } else {
                error("Приложение не авторизовано");
            }
        } else if (ui->radioButtonYandex->isChecked()) {
            valid = settings_.yandexToken().length() > 0;

            if (valid) {
                hide();
                app_.setUploadService(UploadService::YANDEX);
                app_.yandex().setToken(settings_.yandexToken());
            } else {
                error("Приложение не авторизовано");
            }
        }
    } else {
        settings_.create();
    }

    if (valid) {
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

    if (ui->radioButtonServer->isChecked()) {
        settings_.setService(UploadService::SERVER);
    } else if (ui->radioButtonDropbox->isChecked()) {
        settings_.setService(UploadService::DROPBOX);
    } else if (ui->radioButtonYandex->isChecked()) {
        settings_.setService(UploadService::YANDEX);
    }

    settings_.setAutostartup(autoStartupValue);
    settings_.setServerUrl(ui->serverEdit->text());

    AutoStartup autoStartup;
    autoStartup.set(autoStartupValue);
}

void SettingsForm::showAuthDropbox() {
    oauth_.setService(UploadService::DROPBOX);
    oauth_.show();
}

void SettingsForm::showAuthYandex() {
    oauth_.setService(UploadService::YANDEX);
    oauth_.show();
}
