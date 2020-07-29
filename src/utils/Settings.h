#pragma once

#include "src/services/lib/UploadService.h"

#include <QSettings>

class Settings {
public:
    Settings();

    bool autostartup() const;
    void setAutostartup(const bool);

    UploadService service() const;
    void setService(const UploadService);

    QString serverUrl() const;
    void setServerUrl(const QString&);

    QString dropboxToken() const;
    void setDropboxToken(const QString&);

    QString yandexToken() const;
    void setYandexToken(const QString&);

    QString googleToken() const;
    void setGoogleToken(const QString&);

    QString googleRefreshToken() const;
    void setGoogleRefreshToken(const QString&);

    QString googleFolderId() const;
    void setGoogleFolderId(const QString&);

private:
    QSettings settings_;
};
