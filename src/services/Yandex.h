#pragma once

#include "lib/AbstractService.h"

#include <QNetworkReply>

class Yandex : public AbstractService {
    Q_OBJECT

public:
    Yandex();

    void upload(const QByteArray&);
    void setToken(const QString&);

private slots:
    void onUploadReply(QNetworkReply*);
    void onPutReply(QNetworkReply*);
    void onPublishReply(QNetworkReply*);
    void onInfoReply(QNetworkReply*);

private:
    const QByteArray* image_;
    QString token_;
    QNetworkAccessManager manager_;
    QString filename_;
};
