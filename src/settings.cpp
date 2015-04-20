#include "settings.h"

Settings::Settings() :
    _settings(new QSettings("screenshotgun"))
{
}

Settings::~Settings()
{
    delete _settings;
}

bool Settings::exists()
{
    return _settings->contains("common/autostartup");
}

bool Settings::autostartup()
{
    return _settings->value("common/autostartup").toBool();
}

bool Settings::serverChecked()
{
    return _settings->value("server/checked").toBool();
}

QString Settings::serverUrl()
{
    return _settings->value("server/url").toString();
}

void Settings::setAutostartup(bool value)
{
    _settings->setValue("common/autostartup", value);
}

void Settings::setServerChecked(bool value)
{
    _settings->setValue("server/checked", value);
}

void Settings::setServerUrl(QString value)
{
    _settings->setValue("server/url", value);
}
