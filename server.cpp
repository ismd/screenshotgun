#include "server.h"

#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkAccessManager>

Server::Server(QObject *parent) :
    QObject(parent)
{
}

void Server::upload(const QString &filename)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    /*QHttpPart metaPart;
    metaPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    metaPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"metadata\""));
    metaPart.setBody(meta.toJson());
    multiPart->append(metaPart);*/

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"screen.png\""));

    QFile *buffer = new QFile(filename);
    buffer->open(QIODevice::ReadOnly);

    imagePart.setBodyDevice(buffer);
    buffer->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(imagePart);

    QUrl url("http://192.168.1.144/screen/upload");
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply

    connect(reply, SIGNAL(finished()), this, SLOT(uploaded()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void Server::error(QNetworkReply::NetworkError code)
{
    qDebug() << "Error while uploading";
}

void Server::uploaded()
{
    qDebug() << "Uploaded";
}
