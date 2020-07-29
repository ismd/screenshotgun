#include "SettingsForm.h"

#include "src/Context.h"

#include "src/utils/AutoStartup.h"
#include "src/utils/Changelog.h"

SettingsForm::SettingsForm() {
    ui.setupUi(this);

    ui.changelogTextEdit->setPlainText(changelogText);

    connect(ui.authDropbox, &QPushButton::clicked, this, &SettingsForm::showAuthDropbox);
    connect(ui.authYandex, &QPushButton::clicked, this, &SettingsForm::showAuthYandex);
    connect(ui.authGoogle, &QPushButton::clicked, this, &SettingsForm::showAuthGoogle);
}

void SettingsForm::show() {
    Context &ctx = Context::getInstance();

    switch (ctx.settings.service()) {
    case UploadService::SERVER:
        ui.radioButtonServer->setChecked(true);
        break;

    case UploadService::DROPBOX:
        ui.radioButtonDropbox->setChecked(true);
        break;

    case UploadService::YANDEX:
        ui.radioButtonYandex->setChecked(true);
        break;

    case UploadService::GOOGLE:
        ui.radioButtonGoogle->setChecked(true);
        break;

    case UploadService::CLIPBOARD:
        ui.radioButtonClipboard->setChecked(true);
        break;
    }

    ui.autoStartupCheckBox->setChecked(ctx.settings.autostartup());
    ui.serverEdit->setText(ctx.settings.serverUrl());

    ui.errorLabel->setVisible(false);
    ui.submitButtons->setEnabled(true);

    QDialog::show();
    activateWindow();
    raise();
}

bool SettingsForm::check() {
    Context& ctx = Context::getInstance();

    if (ui.radioButtonServer->isChecked()) {
        if (ui.serverEdit->text().isEmpty()) {
            setError("No server url");
            return false;
        }
    } else if (ui.radioButtonDropbox->isChecked()) {
        if (ctx.settings.dropboxToken().isEmpty()) {
            setError("Application is not authorised");
            return false;
        }
    } else if (ui.radioButtonYandex->isChecked()) {
        if (ctx.settings.yandexToken().isEmpty()) {
            setError("Application is not authorised");
            return false;
        }
    } else if (ui.radioButtonGoogle->isChecked()) {
        if (ctx.settings.googleToken().isEmpty()) {
            setError("Application is not authorised");
            return false;
        }
    }

    return true;
}

void SettingsForm::saveValues() {
    Context& ctx = Context::getInstance();
    bool autoStartupValue = ui.autoStartupCheckBox->isChecked();

    if (ui.radioButtonServer->isChecked()) {
        ctx.settings.setService(UploadService::SERVER);
        ctx.server.setUrl(ui.serverEdit->text());
    } else if (ui.radioButtonDropbox->isChecked()) {
        ctx.settings.setService(UploadService::DROPBOX);
        ctx.dropbox.setToken(ctx.settings.dropboxToken());
    } else if (ui.radioButtonYandex->isChecked()) {
        ctx.settings.setService(UploadService::YANDEX);
        ctx.yandex.setToken(ctx.settings.yandexToken());
    } else if (ui.radioButtonGoogle->isChecked()) {
        ctx.settings.setService(UploadService::GOOGLE);
        ctx.google.setToken(ctx.settings.googleToken());
    } else if (ui.radioButtonClipboard->isChecked()) {
        ctx.settings.setService(UploadService::CLIPBOARD);
    }

    ctx.settings.setAutostartup(autoStartupValue);
    ctx.settings.setServerUrl(ui.serverEdit->text());

    AutoStartup::set(autoStartupValue);
}

void SettingsForm::setError(const QString& message) {
    ui.errorLabel->setText(message);
    ui.errorLabel->setVisible(message != "");
}

void SettingsForm::accept() {
    setError("");
    ui.submitButtons->setEnabled(false);

    if (check()) {
        saveValues();
        hide();
    }

    ui.submitButtons->setEnabled(true);
}

void SettingsForm::showAuthDropbox() {
    oauth.setService(UploadService::DROPBOX);
    oauth.show();
}

void SettingsForm::showAuthYandex() {
    oauth.setService(UploadService::YANDEX);
    oauth.show();
}

void SettingsForm::showAuthGoogle() {
    oauth.setService(UploadService::GOOGLE);
    oauth.show();
}
