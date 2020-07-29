#include "Google.h"
#include "src/Context.h"
#include "lib/generateFilename.h"

#include <QHttpMultiPart>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Google::Google() : needReupload_(false) {
}

void Google::upload(const QByteArray& image) {
    image_ = &image;

    filename_ = generateFilename();
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

    QString json = "{\"title\": \"" + filename_ + "\", \"parents\": [{\"id\": \"" + Context::getInstance().settings.googleFolderId() + "\"}]}";
    textPart.setBody(QJsonDocument::fromJson(json.toLatin1()).toJson(QJsonDocument::Compact));

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setBody(image);

    multiPart->append(textPart);
    multiPart->append(imagePart);

    QNetworkRequest request;
    request.setUrl(QUrl("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onUploadReply(QNetworkReply*)));

    multiPart->setParent(manager_.post(request, multiPart)); // Delete the multiPart with the reply
}

void Google::setToken(const QString& token) {
    token_ = token;

    if (Context::getInstance().settings.googleFolderId().length() == 0) {
        getFolder();
    }
}

void Google::getFolder() {
    qDebug() << "Getting Google Drive folder";

    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/files?q=title+%3d+%27Screenshotgun%27+and+mimeType+%3d+%27application/vnd.google-apps.folder%27+and+trashed+=+false+and+properties+has+{+key%3d%27for_screenshots%27+and+value%3d%27true%27+and+visibility%3d%27PRIVATE%27+}"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onGetFolderReply(QNetworkReply*)));

    manager_.get(request);
}

void Google::onUploadReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(onUploadReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();

    if (QNetworkReply::NoError != reply->error()) {
        int code = jsonObject["error"].toObject()["code"].toInt();

        if (code == 401) {
            connect(&Context::getInstance().settingsForm.oauth, SIGNAL(tokenRefreshed()),
                this, SLOT(reupload()));
            emit onRefreshToken(UploadService::GOOGLE);
        } else if (code == 404) {
            needReupload_ = true;
            getFolder();
        } else {
            emit onUploadError(jsonObject["error"].toObject()["message"].toString());
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
                this, SLOT(onShareReply(QNetworkReply*)));

        manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
    }

    delete reply;
}

void Google::onShareReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onShareReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        emit onUploadError(jsonObject["error"].toObject()["message"].toString());
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
    } else {
        emit onUploadSuccess(uploadLink_);
    }

    delete reply;
}

void Google::onGetFolderReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onGetFolderReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        if (jsonObject["error"].toObject()["code"].toInt() == 401) {
            emit onRefreshToken(UploadService::GOOGLE);
        } else {
            needReupload_ = false;
            Context::getInstance().trayIcon.showMessage("Error", "Can't get Google Drive folder", QSystemTrayIcon::Critical, 10000);
            qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
        }
    } else if (jsonObject["items"].toArray().isEmpty()) {
        createFolder();
    } else {
        Context::getInstance().settings.setGoogleFolderId(jsonObject["items"].toArray()[0].toObject()["id"].toString());

        if (needReupload_) {
            needReupload_ = false;
            reupload();
        }
    }

    delete reply;
}

void Google::onCreateFolderReply(QNetworkReply* reply) {
    disconnect(&manager_, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(onCreateFolderReply(QNetworkReply*)));

    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
        needReupload_ = false;
    } else {
        Context::getInstance().settings.setGoogleFolderId(jsonObject["id"].toString());

        if (needReupload_) {
            needReupload_ = false;
            upload(*image_);
        }
    }

    delete reply;
}

void Google::reupload() {
    disconnect(&Context::getInstance().settingsForm.oauth, SIGNAL(tokenRefreshed()),
               this, SLOT(reupload()));

    upload(*image_);
}

void Google::createFolder() {
    qDebug() << "Creating Google Drive folder";
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/files"));
    request.setRawHeader("Authorization", QString("Bearer " + token_).toLatin1());
    request.setRawHeader("Content-Type", "application/json");

    QJsonObject json;
    json["title"] = QString("Screenshotgun");
    json["mimeType"] = QString("application/vnd.google-apps.folder");

    QJsonObject property;
    property["key"] = QString("for_screenshots");
    property["value"] = QString("true");
    property["visibility"] = QString("PRIVATE");

    QJsonArray properties;
    properties.append(property);
    json["properties"] = properties;

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onCreateFolderReply(QNetworkReply*)));

    manager_.post(request, QJsonDocument(json).toJson(QJsonDocument::Compact));
}
