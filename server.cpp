#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
}

void Server::upload()
{
    QString filename = "/home/ismd/Загрузки/tmp.png";

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"screen.png\""));

    QFile *buffer = new QFile(filename);
    buffer->open(QIODevice::ReadOnly);

    imagePart.setBodyDevice(buffer);
    buffer->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(imagePart);

    QUrl url("http://localhost:7998/screen/upload");
    QNetworkRequest request;

    request.setUrl(url);
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
