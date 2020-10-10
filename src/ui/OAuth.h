#pragma once

#include "src/utils/Settings.h"
#include "ui_OAuth.h"

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class OAuth : public QDialog {
    Q_OBJECT

public:
    explicit OAuth();

    void setService(const UploadService);
    void accept();

signals:
    void tokenRefreshed();

private slots:
    void onTokenReply(QNetworkReply*);
    void refreshToken(const UploadService);

private:
    void getToken(const QString& url, const QString& clientId, const QString& clientSecret);

    Ui::OAuth ui;
    UploadService service_;
    QNetworkAccessManager manager_;
    bool refreshing_;
};
