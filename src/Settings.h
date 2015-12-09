#ifndef SCREENSHOTGUN_SETTINGS_H
#define SCREENSHOTGUN_SETTINGS_H

#include <QSettings>

enum class UploadService {
    SERVER,
    YANDEX
};

class Settings {
public:
    Settings();

    bool exists() const;
    void create();

    bool autostartup() const;
    UploadService service() const;
    QString serverUrl() const;
    QString yandexToken() const;

    void setAutostartup(const bool);
    void setService(const UploadService);
    void setServerUrl(const QString&);
    void setYandexToken(const QString&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_SETTINGS_H
