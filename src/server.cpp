#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "const.h"
#include "server.h"

Server::Server(QObject *parent) :
    QObject(parent),
    _manager(new QNetworkAccessManager(this))
{
}

Server::Server(QString url, QObject *parent) :
    QObject(parent),
    _manager(new QNetworkAccessManager(this))
{
    setUrl(url);
}

void Server::setUrl(QString url)
{
    if ("http://" == url.left(7) || "https://" == url.left(8)) {
        _url = url;
    } else {
        _url = "http://" + url;
    }
}

void Server::upload(QByteArray bytes)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"screen.png\""));

    imagePart.setBody(bytes);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(QUrl(_url + "/screen/upload"));
    request.setRawHeader("User-Agent", "Screenshotgun client");

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploaded(QNetworkReply*)));

    _reply = _manager->post(request, multiPart);

    _reply->setParent(_manager);
    multiPart->setParent(_reply); // delete the multiPart with the reply
}

void Server::uploaded(QNetworkReply *reply)
{
    disconnect(_manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(uploaded(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (0 == jsonObject["status"].toString().compare("ok")) {
        emit(screenshotUrl(jsonObject["url"].toString()));
    } else {
        emit(uploadError());
    }
}

void Server::version()
{
    QNetworkRequest request;
    request.setUrl(QUrl(_url + "/dist/version"));
    request.setRawHeader("User-Agent", "Screenshotgun client");

    _manager->get(request);

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(versionFromServer(QNetworkReply*)));
}

void Server::versionFromServer(QNetworkReply *reply)
{
    disconnect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(versionFromServer(QNetworkReply*)));

    if (QNetworkReply::NoError != reply->error()) {
        emit(connectionError());
        return;
    }

    emit(serverVersion(QString(reply->readAll().simplified())));
}

void Server::downloadNewVersion()
{
    QNetworkRequest request;

    request.setUrl(_url + URL_NEW_VERSION);
    request.setRawHeader("User-Agent", "Screenshotgun client");

    _reply = _manager->get(request);

    connect(_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(fileDownloaded(QNetworkReply*)));

    connect(_reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(downloadProgressSlot(qint64, qint64)));
}

void Server::fileDownloaded(QNetworkReply *reply)
{
    emit newVersionDownloaded(reply->readAll());
}

void Server::downloadProgressSlot(qint64 read, qint64 total)
{
    emit(downloadProgress(read, total));
}
