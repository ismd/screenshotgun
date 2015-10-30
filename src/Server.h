#ifndef SCREENSHOTGUN_SERVER_H
#define SCREENSHOTGUN_SERVER_H

#include <QtNetwork>

class Server : public QObject {
    Q_OBJECT

public:
    Server(QObject* parent = 0);

    void setUrl(QString);
    void upload(QByteArray);

signals:
    void uploadSuccess(QString);
    void uploadError();

private slots:
    void uploadedSlot(QNetworkReply*);

private:
    QString url_;
    QNetworkAccessManager manager_;
    QNetworkReply* reply_;
};

#endif // SCREENSHOTGUN_SERVER_H
