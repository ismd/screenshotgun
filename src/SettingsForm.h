#ifndef SCREENSHOTGUN_SETTINGSFORM_H
#define SCREENSHOTGUN_SETTINGSFORM_H

#include <QDialog>
#include "ui_Settings.h"

class App;

class SettingsForm : public QDialog {
    Q_OBJECT

public:
    explicit SettingsForm(App&);
    ~SettingsForm();

    void init();
    bool valid();
    void error(const QString&);
    void show();

private slots:
    void accept();

private:
    void saveValues();

    Ui::Settings* ui;
    App& app_;
    Settings& settings_;
};

#endif // SCREENSHOTGUN_SETTINGSFORM_H
