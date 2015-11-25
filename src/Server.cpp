#include <QDebug>
#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "Server.h"

Server::Server(QObject* parent) : QObject(parent) {
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
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

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

    reply_ = manager_.post(request, multiPart);

    reply_->setParent(&manager_);
    multiPart->setParent(reply_); // delete the multiPart with the reply
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

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (0 == jsonObject["status"].toString().compare("ok")) {
        emit uploadSuccess(jsonObject["url"].toString());
    } else {
        emit uploadError();
    }

    delete reply_;
}

void Server::connectionSlot(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(connectionSlot(QNetworkReply*)));

    if (QNetworkReply::NoError != reply->error()) {
        qDebug() << reply->errorString();
        emit connectionError();
        return;
    }

    emit connectionSuccess();
}
