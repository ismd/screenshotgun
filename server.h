#ifndef SERVER_H
#define SERVER_H

#include <QPixmap>
#include <QNetworkReply>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    void upload(const QString &filename);

public slots:
    void error(QNetworkReply::NetworkError code);
    void uploaded();
};

#endif // SERVER_H
