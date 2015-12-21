#include <QHttpMultiPart>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../App.h"
#include "Google.h"

Google::Google(App& app) : app_(app), needReupload_(false) {
}

void Google::setToken(QString token) {
    token_ = token;

    if (app_.settings().googleFolderId().length() == 0) {
        getFolder();
    }
}

void Google::upload(QByteArray image) {
    image_ = image;
    filename_ = helper_.generateFilename();
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

    QString json = "{\"title\": \"" + filename_ + "\", \"parents\": [{\"id\": \"" + app_.settings().googleFolderId() + "\"}]}";
    textPart.setBody(QJsonDocument::fromJson(json.toLatin1()).toJson(QJsonDocument::Compact));

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setBody(image_);

    multiPart->append(textPart);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(QUrl("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(uploadReply(QNetworkReply*)));

    multiPart->setParent(manager_.post(request, multiPart)); // delete the multiPart with the reply
}

void Google::getFolder() {
    qDebug() << "Getting Google Drive folder";

    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/files?q=title+%3d+%27Screenshotgun%27+and+mimeType+%3d+%27application/vnd.google-apps.folder%27+and+trashed+=+false"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getFolderReply(QNetworkReply*)));

    manager_.get(request);
}

void Google::uploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(uploadReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        int code = jsonObject["error"].toObject()["code"].toInt();

        if (code == 401) {
            emit refreshToken(UploadService::GOOGLE);
        } else if (code == 404) {
            needReupload_ = true;
            getFolder();
        } else {
            emit uploadError(jsonObject["error"].toObject()["message"].toString());
            qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
        }
    } else {
        uploadLink_ = jsonObject["alternateLink"].toString();

        QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/files/" + jsonObject["id"].toString() + "/permissions"));
        request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
        request.setRawHeader("Content-Type", "application/json");

        QJsonObject json;
        json["role"] = QString("reader");
        json["type"] = QString("anyone");

        connect(&manager_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(shareReply(QNetworkReply*)));

        manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
    }

    delete reply;
}

void Google::shareReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(shareReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        emit uploadError(jsonObject["error"].toObject()["message"].toString());
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
    } else {
        emit uploadSuccess(uploadLink_);
    }

    delete reply;
}

void Google::getFolderReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(getFolderReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        needReupload_ = false;
        app_.trayIcon().showError("Ошибка", "Не удалось получить папку в Google Drive");
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
    } else if (jsonObject["items"].toArray().isEmpty()) {
        createFolder();
    } else {
        app_.settings().setGoogleFolderId(jsonObject["items"].toArray()[0].toObject()["id"].toString());

        if (needReupload_) {
            needReupload_ = false;
            upload(image_);
        }
    }

    delete reply;
}

void Google::createFolderReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(createFolderReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
        needReupload_ = false;
    } else {
        app_.settings().setGoogleFolderId(jsonObject["id"].toString());

        if (needReupload_) {
            needReupload_ = false;
            upload(image_);
        }
    }

    delete reply;
}

void Google::createFolder() {
    qDebug() << "Creating Google Drive folder";
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/files"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
    request.setRawHeader("Content-Type", "application/json");

    QJsonObject json;
    json["title"] = QString("Screenshotgun");
    json["mimeType"] = QString("application/vnd.google-apps.folder");

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(createFolderReply(QNetworkReply*)));

    manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
}
