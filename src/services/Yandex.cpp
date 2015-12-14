#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include "Yandex.h"

Yandex::Yandex() {
}

void Yandex::setToken(QString token) {
    token_ = token;
}

void Yandex::upload(QByteArray image) {
    image_ = image;

    filename_ = helper_.generateFilename();
    QNetworkRequest request(QUrl("https://cloud-api.yandex.net/v1/disk/resources/upload?path=app:%2F" + filename_));
    request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadReply(QNetworkReply*)));

    manager_.get(request);
}

void Yandex::uploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qDebug() << QString(jsonResponse.toJson());
    } else {
        QNetworkRequest request(QUrl(jsonObject["href"].toString()));

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(putReply(QNetworkReply*)));

        manager_.put(request, image_);
    }
}

void Yandex::putReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(putReply(QNetworkReply*)));

    reply->close();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError("Неизвестная ошибка");
    } else {
        QNetworkRequest request(QUrl("https://cloud-api.yandex.net/v1/disk/resources/publish?path=app:%2F" + filename_));
        request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

        connect(&manager_, SIGNAL(finished(QNetworkReply * )),
                this, SLOT(publishReply(QNetworkReply * )));

        manager_.put(request, "");
    }
}

void Yandex::publishReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(publishReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qDebug() << QString(jsonResponse.toJson());
    } else {
        QNetworkRequest request(QUrl(jsonObject["href"].toString()));
        request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

        connect(&manager_, SIGNAL(finished(QNetworkReply * )),
                this, SLOT(infoReply(QNetworkReply * )));

        manager_.get(request);
    }
}

void Yandex::infoReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(infoReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qDebug() << QString(jsonResponse.toJson());
    } else {
        emit uploadSuccess(jsonObject["public_url"].toString());
    }
}
