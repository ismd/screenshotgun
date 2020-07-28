#pragma once

#include "ServiceHelper.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Dropbox : public QObject {
    Q_OBJECT

public:
    Dropbox();
    void setToken(QString);
    void upload(QByteArray);

signals:
    void uploadSuccess(QString);
    void uploadError(QString);

private slots:
    void uploadReply(QNetworkReply*);
    void shareReply(QNetworkReply*);

private:
    QString token_;
    QNetworkAccessManager manager_;
    QString filename_;
    ServiceHelper helper_;
};
