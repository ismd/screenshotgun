#pragma once

#include "Settings.h"
#include "ui_OAuth.h"

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class App;

class OAuth : public QDialog {
    Q_OBJECT

public:
    explicit OAuth(App&);
    ~OAuth();

    void setService(UploadService);
    void accept();

signals:
    void tokenRefreshed();

private slots:
    void tokenReply(QNetworkReply*);
    void refreshToken(UploadService);

private:
    void getToken(const QString url, const QString clientId, const QString clientSecret);
    App& app_;
    Ui::OAuth* ui;
    UploadService service_;
    QNetworkAccessManager manager_;
    bool refreshing_;
};
