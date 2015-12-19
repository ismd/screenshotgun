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

    connect(ui->authGoogle, SIGNAL(clicked()),
            this, SLOT(showAuthGoogle()));
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

        case UploadService::GOOGLE:
            ui->radioButtonGoogle->setChecked(true);
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
                setError("Не указан адрес сервера");
                ui->submitButtons->setEnabled(true);
            }
        } else if (ui->radioButtonDropbox->isChecked()) {
            valid = settings_.dropboxToken().length() > 0;

            if (valid) {
                hide();
                app_.setUploadService(UploadService::DROPBOX);
                app_.dropbox().setToken(settings_.dropboxToken());
            } else {
                setError("Приложение не авторизовано");
                ui->submitButtons->setEnabled(true);
            }
        } else if (ui->radioButtonYandex->isChecked()) {
            valid = settings_.yandexToken().length() > 0;

            if (valid) {
                hide();
                app_.setUploadService(UploadService::YANDEX);
                app_.yandex().setToken(settings_.yandexToken());
            } else {
                setError("Приложение не авторизовано");
                ui->submitButtons->setEnabled(true);
            }
        } else if (ui->radioButtonGoogle->isChecked()) {
            valid = settings_.googleToken().length() > 0;

            if (valid) {
                hide();
                app_.setUploadService(UploadService::GOOGLE);
                app_.google().setToken(settings_.googleToken());
            } else {
                setError("Приложение не авторизовано");
                ui->submitButtons->setEnabled(true);
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

void SettingsForm::setError(const QString &message) {
    ui->errorLabel->setText(message);

    if ("" != message) {
        ui->errorLabel->setVisible(true);
    } else {
        ui->errorLabel->setVisible(false);
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
    setError("Не удалось подключиться к серверу");
    ui->submitButtons->setEnabled(true);
    show();
}

void SettingsForm::accept() {
    setError("");
    ui->submitButtons->setEnabled(false);
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
    } else if (ui->radioButtonGoogle->isChecked()) {
        settings_.setService(UploadService::GOOGLE);
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

void SettingsForm::showAuthGoogle() {
    oauth_.setService(UploadService::GOOGLE);
    oauth_.show();
}
