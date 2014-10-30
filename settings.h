#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QObject>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    bool isValid();
    QString getServer();

signals:
    void valid(bool);

private slots:
    void accept();

private:
    Ui::Settings *ui;
    QSettings* _settings;
};

#endif // SETTINGS_H
