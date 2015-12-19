#ifndef SCREENSHOTGUN_SERVER_H
#define SCREENSHOTGUN_SERVER_H

#include <QtNetwork>

class Server : public QObject {
    Q_OBJECT

public:
    Server();

    QString url() const;
    void setUrl(const QString&);
    void upload(QByteArray);
    void checkConnection();

signals:
    void connectionSuccess();
    void connectionError();
    void uploadSuccess(QString);
    void uploadError();

private slots:
    void uploadedSlot(QNetworkReply*);
    void connectionSlot(QNetworkReply*);

private:
    QString url_;
    QNetworkAccessManager manager_;
};

#endif // SCREENSHOTGUN_SERVER_H
