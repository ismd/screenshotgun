#ifndef SCREENSHOTGUN_OAUTH_H
#define SCREENSHOTGUN_OAUTH_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "Settings.h"
#include "ui_OAuth.h"

class App;

class OAuth : public QDialog {
    Q_OBJECT

public:
    explicit OAuth(App&);
    ~OAuth();

    void setService(UploadService);
    void accept();

private slots:
    void tokenReply(QNetworkReply*);

private:
    App& app_;
    Ui::OAuth* ui;
    UploadService service_;
    QNetworkAccessManager manager_;
};

#endif //SCREENSHOTGUN_OAUTH_H
