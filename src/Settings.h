#ifndef SCREENSHOTGUN_SETTINGS_H
#define SCREENSHOTGUN_SETTINGS_H

#include <QSettings>

class Settings {
public:
    Settings();

    bool exists() const;

    bool autostartup() const;
    QString serverUrl() const;

    void autostartup(bool);
    void serverUrl(const QString&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_SETTINGS_H
