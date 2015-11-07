#ifndef SCREENSHOTGUN_UPDATER_H
#define SCREENSHOTGUN_UPDATER_H

#include <QDialog>
#include <QProcess>
#include "ui_Update.h"

class Updater : public QDialog {
    Q_OBJECT

public:
    Updater();
    ~Updater();

    void check();
    void update();

signals:
    void noUpdate();

private slots:
    void checkUpdates();
    void accept();

private:
    Ui::Update* ui;
    QProcess process_;
};

#endif //SCREENSHOTGUN_UPDATER_H
