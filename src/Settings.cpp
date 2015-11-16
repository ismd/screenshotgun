#include "Settings.h"

Settings::Settings() : settings_("screenshotgun", "main") {
}

bool Settings::autostartup() const {
    return settings_.value("common/autostartup", false).toBool();
}

QString Settings::serverUrl() const {
    return settings_.value("server/url", "").toString();
}

void Settings::autostartup(const bool value) {
    settings_.setValue("common/autostartup", value);
}

void Settings::serverUrl(const QString& value) {
    settings_.setValue("server/url", value);
}
