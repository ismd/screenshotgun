#pragma once

#include "OAuth.h"
#include "ui_Settings.h"

#include <QDialog>

class SettingsForm : public QDialog {
    Q_OBJECT

public:
    explicit SettingsForm();

    void show();
    bool check();
    void saveValues();
    void setHotkey(const QKeySequence);

    OAuth oauth;


signals:
    void hotkeyChanged(const QKeySequence);

public slots:
    void setError(const QString&);

private slots:
    void accept();

    void showAuthDropbox();
    void showAuthYandex();
    void showAuthGoogle();

private:
    Ui::Settings ui;
};
