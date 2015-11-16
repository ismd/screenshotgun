#ifndef SCREENSHOTGUN_SETTINGS_H
#define SCREENSHOTGUN_SETTINGS_H

#include <QSettings>
#include "Toolbar.h"

class Settings {
public:
    Settings();

    bool autostartup() const;
    QString serverUrl() const;
    ToolbarMode lastTool() const;

    void autostartup(const bool);
    void serverUrl(const QString&);
    void lastTool(const ToolbarMode&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_SETTINGS_H
