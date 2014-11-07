#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QString url, QObject *parent = 0);
    ~Server();
    void upload(QByteArray);

private slots:
    void uploaded(QNetworkReply*);
    void clientVersion(QNetworkReply*);

private:
    QString _url;
    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
};

#endif // SERVER_H
