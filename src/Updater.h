#pragma once

#include "ui_Update.h"

#include <QDialog>
#include <QProcess>

class App;

class Updater : public QDialog {
    Q_OBJECT

public:
    Updater(App&);
    ~Updater();
    void check();

private slots:
    void checkUpdates();
    void accept();
    void errorOccurred(QProcess::ProcessError);

private:
    Ui::Update* ui;
    App& app_;
    QProcess process_;

#if defined(Q_OS_WIN32)
    QString maintenancetool_ = "maintenancetool.exe";
#elif defined(Q_OS_MACOS)
    QString maintenancetool_;
#else
    QString maintenancetool_ = "/bin/false";
#endif
};
