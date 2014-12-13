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
    void downloadNewVersion();

signals:
    void serverVersion(QString);
    void connectionError();
    void newVersionDownloaded(QByteArray);

private slots:
    void uploaded(QNetworkReply*);
    void versionFromServer(QNetworkReply*);
    void fileDownloaded(QNetworkReply*);

private:
    QString _url;
    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
};

#endif // SERVER_H
