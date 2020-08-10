#include "Yandex.h"
#include "lib/generateFilename.h"

#include <QBuffer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

Yandex::Yandex() {
}

void Yandex::upload(const QImage& image) {
    image_ = &image;

    filename_ = generateFilename();
    QNetworkRequest request(QUrl("https://cloud-api.yandex.net/v1/disk/resources/upload?path=app:%2F" + filename_));
    request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onUploadReply(QNetworkReply*)));

    manager_.get(request);
}

void Yandex::setToken(const QString& token) {
    token_ = token;
}

void Yandex::onUploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onUploadReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qInfo() << QString(jsonResponse.toJson(QJsonDocument::Compact));
    } else {
        QNetworkRequest request(jsonObject["href"].toString());

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(onPutReply(QNetworkReply*)));

        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        image_->save(&buffer, "PNG");

        manager_.put(request, bytes);
    }

    delete reply;
}

void Yandex::onPutReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onPutReply(QNetworkReply*)));

    reply->close();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError("Unknown error");
    } else {
        QNetworkRequest request("https://cloud-api.yandex.net/v1/disk/resources/publish?path=app:%2F" + filename_);
        request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(onPublishReply(QNetworkReply*)));

        manager_.put(request, "");
    }

    delete reply;
}

void Yandex::onPublishReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onPublishReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qInfo() << QString(jsonResponse.toJson(QJsonDocument::Compact));
    } else {
        QNetworkRequest request(jsonObject["href"].toString());
        request.setRawHeader("Authorization", QString("OAuth " + token_).toLatin1());

        connect(&manager_, SIGNAL(finished(QNetworkReply * )),
                this, SLOT(onInfoReply(QNetworkReply * )));

        manager_.get(request);
    }

    delete reply;
}

void Yandex::onInfoReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onInfoReply(QNetworkReply*)));

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["message"].toString());
        qInfo() << QString(jsonResponse.toJson(QJsonDocument::Compact));
    } else {
        QString url = jsonObject["public_url"].toString();
        emit uploadSuccess(url);
    }

    delete reply;
}
