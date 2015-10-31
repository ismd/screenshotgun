#include "Settings.h"

Settings::Settings() : settings_("screenshotgun") {
}

bool Settings::exists() const {
    return settings_.contains("common/autostartup");
}

bool Settings::autostartup() const {
    return settings_.value("common/autostartup", false).toBool();
}

QString Settings::serverUrl() const {
    return settings_.value("server/url", "").toString();
}

void Settings::autostartup(bool value) {
    settings_.setValue("common/autostartup", value);
}

void Settings::serverUrl(const QString& value) {
    settings_.setValue("server/url", value);
}
