#ifndef SCREENSHOTGUN_YANDEX_H
#define SCREENSHOTGUN_YANDEX_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ServiceHelper.h"

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

#endif //SCREENSHOTGUN_YANDEX_H
