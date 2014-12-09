#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    Server(QString url, QObject *parent = 0);
    ~Server();
    void setUrl(QString);
    void upload(QByteArray);
    void version();

signals:
    void serverVersion(QString);

private slots:
    void uploaded(QNetworkReply*);
    void versionFromServer(QNetworkReply*);

private:
    QString _url;
    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
};

#endif // SERVER_H
