#include "Dropbox.h"
#include "lib/generateFilename.h"

#include <QBuffer>
#include <QJsonDocument>
#include <QJsonObject>

Dropbox::Dropbox() {
}

void Dropbox::upload(const QImage& image) {
    filename_ = generateFilename();
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/upload"));

    QJsonObject json;
    json["path"] = "/" + filename_;
    json["mode"] = QString("add");

    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
    request.setRawHeader("Content-Type", "application/octet-stream");
    request.setRawHeader("Dropbox-API-Arg", QJsonDocument(json).toJson(QJsonDocument::Compact));

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onUploadReply(QNetworkReply*)));

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    manager_.post(request, bytes);
}

void Dropbox::setToken(const QString& token) {
    token_ = token;
}

void Dropbox::onUploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onUploadReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["error_summary"].toString());
        qInfo() << result;
    } else {
        QNetworkRequest request(QUrl("https://api.dropboxapi.com/2/sharing/create_shared_link"));

        request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
        request.setRawHeader("Content-Type", "application/json");

        QJsonObject json;
        json["path"] = "/" + filename_;
        json["short_url"] = true;

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(onShareReply(QNetworkReply*)));

        manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
    }

    delete reply;
}

void Dropbox::onShareReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onShareReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["error_summary"].toString());
        qInfo() << result;
    } else {
        QString url = jsonObject["url"].toString();
        emit uploadSuccess(url);
    }

    delete reply;
}
