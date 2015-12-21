#ifndef SCREENSHOTGUN_DROPBOX_H
#define SCREENSHOTGUN_DROPBOX_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ServiceHelper.h"

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

#endif //SCREENSHOTGUN_DROPBOX_H
