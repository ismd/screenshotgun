#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>
#include <QObject>
#include <QSettings>
#include "settings.h"

namespace Ui {
    class Settings;
}

class SettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(Settings*, QWidget *parent = 0);
    ~SettingsForm();
    bool isValid();
    QString server();
    SettingsForm* setError(QString);
    void show();

signals:
    void valid();

private slots:
    void accept();

private:
    Ui::Settings *ui;
    Settings* _settings;
};

#endif // SETTINGSFORM_H
