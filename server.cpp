#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include "server.h"
#include <QDebug>
#include <QPixmap>

Server::Server(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
}

Server::~Server()
{
    delete _manager;
}

void Server::upload(QString url, QByteArray bytes)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"screen.png\""));

    imagePart.setBody(bytes);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(QUrl("http://" + url + "/screen/upload"));
    request.setRawHeader("User-Agent", "OpenScreenCloud client");

    _reply = _manager->post(request, multiPart);
    multiPart->setParent(_reply); // delete the multiPart with the reply
}

void Server::finished(QNetworkReply *reply)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (0 == jsonObject["status"].toString().compare("ok")) {
        qDebug() << jsonObject["url"].toString();
    }
}
