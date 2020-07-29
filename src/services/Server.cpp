#include "Server.h"
#include "src/Context.h"

#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>

const int MAX_CONNECTION_CHECKS = 3;

Server::Server() : connected_(false), connectionChecks_(0) {
}

QString Server::url() const {
    return url_;
}

void Server::setUrl(const QString& url) {
    connected_ = false;
    connectionChecks_ = 0;

    if (url.startsWith("http://") || url.startsWith("https://")) {
        url_ = url;
    } else {
        url_ = "http://" + url;
    }

    checkConnection();
}

bool Server::connected() const {
    return connected_;
}

void Server::upload(const QByteArray& bytes) {
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"screen.png\"");

    imagePart.setBody(bytes);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(url_ + "/screen/upload");
    request.setRawHeader("User-Agent", "Screenshotgun client");

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadedSlot(QNetworkReply*)));

    QNetworkReply* reply = manager_.post(request, multiPart);
    multiPart->setParent(reply); // Delete the multiPart with the reply
}

void Server::uploaded(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(uploadedSlot(QNetworkReply*)));

    if (reply->error() != QNetworkReply::NoError) {
        emit onUploadError("Error while uploading screenshot");
    } else {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        reply->close();

        QJsonObject jsonObject = jsonResponse.object();

        if (jsonObject["status"].toString().compare("ok") == 0) {
            QString url = jsonObject["url"].toString();
            emit onUploadSuccess(url);
        } else {
            emit onUploadError("Error at server side while uploading screenshot");
        }
    }

    reply->deleteLater();
}

void Server::onConnected(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onConnected(QNetworkReply*)));

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Can't connect to" << url_ << "Attempt #" << connectionChecks_;

        if (connectionChecks_ == 0) {
            startTimer(20000);
        }

        connectionChecks_++;
        emit onConnectionError();
    } else {
        qDebug() << "Connection established to" << url_;

        connected_ = true;
        emit onConnectionSuccess();
    }

    reply->deleteLater();
}

void Server::checkConnection() {
    connectionChecks_++;

    QNetworkRequest request(url_);
    request.setRawHeader("User-Agent", "Screenshotgun client");

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onConnected(QNetworkReply*)));

    manager_.get(request);
}

void Server::timerEvent(QTimerEvent* event) {
    if (connected_) {
        killTimer(event->timerId());
        return;
    }

    if (connectionChecks_ == MAX_CONNECTION_CHECKS) {
        killTimer(event->timerId());
        emit onConnectionFailed();
        return;
    }

    checkConnection();
}
