#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "Server.h"

Server::Server() {
}

QString Server::url() const {
    return url_;
}

void Server::setUrl(const QString& url) {
    if ("http://" == url.left(7) || "https://" == url.left(8)) {
        url_ = url;
    } else {
        url_ = "http://" + url;
    }

    checkConnection();
}

void Server::upload(QByteArray bytes) {
    auto multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"screen.png\""));

    imagePart.setBody(bytes);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(QUrl(url_ + "/screen/upload"));
    request.setRawHeader("User-Agent", "Screenshotgun client");

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadedSlot(QNetworkReply*)));

    QNetworkReply* reply = manager_.post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
}

void Server::checkConnection() {
    QNetworkRequest request(url_);
    request.setRawHeader("User-Agent", "Screenshotgun client");

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(connectionSlot(QNetworkReply*)));

    manager_.get(request);
}

void Server::uploadedSlot(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(uploadedSlot(QNetworkReply*)));

    if (reply->error() != QNetworkReply::NoError) {
        emit uploadError();
    } else {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        reply->close();

        QJsonObject jsonObject = jsonResponse.object();

        if (0 == jsonObject["status"].toString().compare("ok")) {
            emit uploadSuccess(jsonObject["url"].toString());
        } else {
            emit uploadError();
        }
    }

    reply->deleteLater();
}

void Server::connectionSlot(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(connectionSlot(QNetworkReply*)));

    if (reply->error() != QNetworkReply::NoError) {
        emit connectionError();
    } else {
        emit connectionSuccess();
    }

    reply->deleteLater();
}
