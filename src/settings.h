#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>

class Settings
{
public:
    Settings();
    ~Settings();

    bool exists();

    bool autostartup();
    bool serverChecked();
    QString serverUrl();

    void setAutostartup(bool);
    void setServerChecked(bool);
    void setServerUrl(QString);

private:
    QSettings* _settings;
};

#endif // SETTINGS_H
