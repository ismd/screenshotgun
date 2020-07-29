#pragma once

#include "lib/AbstractService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Server : public AbstractService {
    Q_OBJECT

public:
    Server();

    void upload(const QByteArray&);

    /**
     * Url of remote server for uploading
     */
    QString url() const;

    /**
     * Sets url of remote server for uploading
     */
    void setUrl(const QString&);

    bool connected() const;

signals:
    void onConnectionSuccess();

    /**
     * Emits on connection failed
     */
    void onConnectionError();

    /**
     * Emits after MAX_CONNECTION_CHECKS errors
     */
    void onConnectionFailed();

private slots:
    void uploaded(QNetworkReply*);
    void onConnected(QNetworkReply*);

private:
    void checkConnection();
    void timerEvent(QTimerEvent*);

    QString url_;
    QNetworkAccessManager manager_;
    bool connected_;
    int connectionChecks_;
};
