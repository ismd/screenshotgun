#include "Settings.h"

#include <QKeySequence>

Settings::Settings() : settings_("screenshotgun", "main") {
    // If settings file not exists
    if (!settings_.contains("common/autostartup")) {
        setAutostartup(false);
    }
}

bool Settings::autostartup() const {
    return settings_.value("common/autostartup", false).toBool();
}

void Settings::setAutostartup(const bool value) {
  settings_.setValue("common/autostartup", value);
}

UploadService Settings::service() const {
    return static_cast<UploadService>(settings_.value("common/service", static_cast<int>(UploadService::SERVER)).toInt());
}

void Settings::setService(const UploadService value) {
  settings_.setValue("common/service", static_cast<int>(value));
}

QString Settings::serverUrl() const {
    return settings_.value("server/url", "screenshotgun.com").toString();
}

void Settings::setServerUrl(const QString &value) {
  settings_.setValue("server/url", value);
}

QString Settings::dropboxToken() const {
    return settings_.value("dropbox/token", "").toString();
}

void Settings::setDropboxToken(const QString &value) {
  settings_.setValue("dropbox/token", value);
}

QString Settings::yandexToken() const {
    return settings_.value("yandex/token", "").toString();
}

void Settings::setYandexToken(const QString &value) {
  settings_.setValue("yandex/token", value);
}

QString Settings::googleToken() const {
    return settings_.value("google/token", "").toString();
}

void Settings::setGoogleToken(const QString &value) {
  settings_.setValue("google/token", value);
}

QString Settings::googleRefreshToken() const {
    return settings_.value("google/refresh_token", "").toString();
}

void Settings::setGoogleRefreshToken(const QString &value) {
  settings_.setValue("google/refresh_token", value);
}

QString Settings::googleFolderId() const {
    return settings_.value("google/folder_id", "").toString();
}

void Settings::setGoogleFolderId(const QString& value) {
    settings_.setValue("google/folder_id", value);
}

QKeySequence Settings::hotkey() const {
    return static_cast<QKeySequence>(settings_.value("common/hotkey", QKeySequence(Qt::ALT + Qt::Key_Print)).toString());
}

void Settings::setHotkey(const QKeySequence seq) {
    settings_.setValue("common/hotkey", seq);
}
