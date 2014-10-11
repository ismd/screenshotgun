#include "server.h"

#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(QObject *parent) :
    QObject(parent)
{
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

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply

    connect(reply, SIGNAL(finished()),
            this,  SLOT(uploadSuccess()));
}

/*void Server::upload(const QObject *image)
{
    QPixmap *pixmap = qobject_cast<QPixmap*>(image);

    QFile file("/home/ismd/Загрузки/tmp.png");
    file.open(QIODevice::WriteOnly);
    pixmap->save(&file, "PNG");
    file.close();

    //this->upload("/home/ismd/Загрузки/tmp.png");
}*/

void Server::uploadSuccess()
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (0 == jsonObject["status"].toString().compare("ok")) {
        qDebug() << jsonObject["url"].toString();
    }
}
