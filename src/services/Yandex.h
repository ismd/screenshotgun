#pragma once

#include "ServiceHelper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Yandex : public QObject {
    Q_OBJECT

public:
    Yandex();
    void setToken(QString);
    void upload(QByteArray);

signals:
    void uploadSuccess(QString);
    void uploadError(QString);

private slots:
    void uploadReply(QNetworkReply*);
    void putReply(QNetworkReply*);
    void publishReply(QNetworkReply*);
    void infoReply(QNetworkReply*);

private:
    QString token_;
    QNetworkAccessManager manager_;
    QByteArray image_;
    QString filename_;
    ServiceHelper helper_;
};
