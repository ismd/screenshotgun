#include "Settings.h"

Settings::Settings() : settings_("screenshotgun") {
}

bool Settings::autostartup() const {
    return settings_.value("common/autostartup", false).toBool();
}

QString Settings::serverUrl() const {
    return settings_.value("server/url", "").toString();
}

ToolbarMode Settings::lastTool() const {
    int value = settings_.value("common/last_tool", static_cast<int>(ToolbarMode::ARROW)).toInt();

    switch (value) {
        case static_cast<int>(ToolbarMode::LINE):
            return ToolbarMode::LINE;

        case static_cast<int>(ToolbarMode::ARROW):
            return ToolbarMode::ARROW;

        case static_cast<int>(ToolbarMode::RECT):
            return ToolbarMode::RECT;

        default:
            return ToolbarMode::ARROW;
    }
}

void Settings::autostartup(const bool value) {
    settings_.setValue("common/autostartup", value);
}

void Settings::serverUrl(const QString& value) {
    settings_.setValue("server/url", value);
}

void Settings::lastTool(const ToolbarMode& value) {
    settings_.setValue("common/last_tool", static_cast<int>(value));
}
