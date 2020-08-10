#pragma once

#include "lib/AbstractService.h"

#include <QNetworkReply>

class Dropbox : public AbstractService {
    Q_OBJECT

public:
    Dropbox();

    void upload(const QImage&);
    void setToken(const QString&);

private slots:
    void onUploadReply(QNetworkReply*);
    void onShareReply(QNetworkReply*);

private:
    QString token_;
    QNetworkAccessManager manager_;
    QString filename_;
};
