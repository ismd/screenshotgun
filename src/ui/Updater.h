#pragma once

#include "ui_Update.h"

#include <QDialog>
#include <QProcess>

class Updater : public QDialog {
    Q_OBJECT

public:
    Updater();

    void check();

private slots:
    void onCheckUpdates();
    void accept();
    void onErrorOccurred(QProcess::ProcessError);

private:
    Ui::Update ui;
    QProcess process_;

#if defined(Q_OS_LINUX)
    QString maintenancetool_ = "/bin/false";
#elif defined(Q_OS_WIN32)
    QString maintenancetool_ = "maintenancetool.exe";
#elif defined(Q_OS_MACOS)
    QString maintenancetool_;
#endif
};
