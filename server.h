#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    void upload();

private slots:
    void finished(QNetworkReply*);

private:
    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
};

#endif // SERVER_H
