#include <QJsonDocument>
#include <QJsonObject>
#include "Dropbox.h"

Dropbox::Dropbox() {
}

void Dropbox::setToken(QString token) {
    token_ = token;
}

void Dropbox::upload(QByteArray image) {
    filename_ = helper_.generateFilename();
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/upload"));

    QJsonObject json;
    json["path"] = "/" + filename_;
    json["mode"] = "add";

    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
    request.setRawHeader("Content-Type", "application/octet-stream");
    request.setRawHeader("Dropbox-API-Arg", QJsonDocument(json).toJson(QJsonDocument::Compact));

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadReply(QNetworkReply*)));

    manager_.post(request, image);
}

void Dropbox::uploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["error_summary"].toString());
        qDebug() << result;
    } else {
        QNetworkRequest request(QUrl("https://api.dropboxapi.com/2/sharing/create_shared_link"));

        request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
        request.setRawHeader("Content-Type", "application/json");

        QJsonObject json;
        json["path"] = "/" + filename_;
        json["short_url"] = true;

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(shareReply(QNetworkReply*)));

        manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
    }

    delete reply;
}

void Dropbox::shareReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(shareReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["error_summary"].toString());
        qDebug() << result;
    } else {
        emit uploadSuccess(jsonObject["url"].toString());
    }

    delete reply;
}
