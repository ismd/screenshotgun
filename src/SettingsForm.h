#ifndef SCREENSHOTGUN_SETTINGSFORM_H
#define SCREENSHOTGUN_SETTINGSFORM_H

#include <QDialog>
#include "OAuth.h"
#include "ui_Settings.h"

class App;

class SettingsForm : public QDialog {
    Q_OBJECT

public:
    explicit SettingsForm(App&);
    ~SettingsForm();

    void init();
    bool valid(const bool save);
    void setError(const QString&);
    void show();
    void showCantConnect();
    OAuth& oauth();

private slots:
    void accept();
    void showAuthDropbox();
    void showAuthYandex();
    void showAuthGoogle();

private:
    void saveValues();

    Ui::Settings* ui;
    App& app_;
    Settings& settings_;
    OAuth oauth_;
};

#endif // SCREENSHOTGUN_SETTINGSFORM_H
