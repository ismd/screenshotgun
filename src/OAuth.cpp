#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrlQuery>
#include "App.h"
#include "OAuth.h"

const QString DROPBOX_URL = "https://api.dropboxapi.com/1/oauth2/token";
const QString DROPBOX_CLIENT_ID = "wmae5esncijnqie";
const QString DROPBOX_CLIENT_SECRET = "3fp3vak8ijd1l1e";

const QString YANDEX_URL = "https://oauth.yandex.ru/token";
const QString YANDEX_CLIENT_ID = "9cc4557692e44328bfecf32f2c131eea";
const QString YANDEX_CLIENT_SECRET = "1d2e753854d946ea80f3880c11c5f76e";

const QString GOOGLE_URL = "https://www.googleapis.com/oauth2/v4/token";
const QString GOOGLE_CLIENT_ID = "445396168271-7bankmpva981k4d74ebi11o7avgle1qa.apps.googleusercontent.com";
const QString GOOGLE_CLIENT_SECRET = "_QjArq04n7dFs3TgyyB5w3D-";

OAuth::OAuth(App& app) : app_(app), ui(new Ui::OAuth), refreshing_(false) {
    ui->setupUi(this);

    connect(&manager_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tokenReply(QNetworkReply*)));

    // Refresh tokens
    connect(&app_.google(), SIGNAL(refreshToken(UploadService)),
            this, SLOT(refreshToken(UploadService)));
}

OAuth::~OAuth() {
    delete ui;
}

void OAuth::setService(UploadService service) {
    service_ = service;
    QString text("1. Откройте в браузере <a href=\"{LINK}\">ссылку</a>.");

    switch (service) {
        case UploadService::DROPBOX:
            text.replace("{LINK}", "https://www.dropbox.com/1/oauth2/authorize?response_type=code&client_id=" + DROPBOX_CLIENT_ID);
            break;

        case UploadService::YANDEX:
            text.replace("{LINK}", "https://oauth.yandex.ru/authorize?response_type=code&client_id=" + YANDEX_CLIENT_ID);
            break;

        case UploadService::GOOGLE:
            text.replace("{LINK}", "https://accounts.google.com/o/oauth2/v2/auth?response_type=code&scope=https://www.googleapis.com/auth/drive.file&redirect_uri=urn:ietf:wg:oauth:2.0:oob&client_id=" + GOOGLE_CLIENT_ID);
            break;
    }

    ui->link->setText(text.replace("{LINK}", text));
}

void OAuth::accept() {
    ui->submitButtons->setEnabled(false);

    switch (service_) {
        case UploadService::DROPBOX:
            getToken(DROPBOX_URL, DROPBOX_CLIENT_ID, DROPBOX_CLIENT_SECRET);
            break;

        case UploadService::YANDEX:
            getToken(YANDEX_URL, YANDEX_CLIENT_ID, YANDEX_CLIENT_SECRET);
            break;

        case UploadService::GOOGLE:
            getToken(GOOGLE_URL, GOOGLE_CLIENT_ID, GOOGLE_CLIENT_SECRET);
            break;
    }
}

void OAuth::tokenReply(QNetworkReply* reply) {
    ui->submitButtons->setEnabled(true);

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    reply->close();

    QJsonObject jsonObject = jsonResponse.object();
    if (QNetworkReply::NoError != reply->error()) {
        app_.trayIcon().showError("Ошибка", jsonObject["error_description"].toString());
        qDebug() << jsonResponse.toJson(QJsonDocument::Compact);
    } else {
        hide();

        QString token = jsonObject["access_token"].toString();
        switch (service_) {
            case UploadService::DROPBOX:
                app_.settings().setDropboxToken(token);
                app_.dropbox().setToken(token);
                break;

            case UploadService::YANDEX:
                app_.settings().setYandexToken(token);
                app_.yandex().setToken(token);
                break;

            case UploadService::GOOGLE:
                app_.settings().setGoogleToken(token);
                app_.google().setToken(token);

                QString refreshToken = jsonObject["refresh_token"].toString();
                if (refreshToken.length() > 0) {
                    app_.settings().setGoogleRefreshToken(refreshToken);
                }
                break;
        }

        app_.settingsForm().setError("");

        if (!refreshing_) {
            app_.settingsForm().show();
        }

        emit tokenRefreshed();
    }

    refreshing_ = false;
}

void OAuth::refreshToken(UploadService service) {
    qDebug() << "Refreshing token";
    service_ = service;
    refreshing_ = true;

    switch (service) {
        case UploadService::GOOGLE:
            getToken(GOOGLE_URL, GOOGLE_CLIENT_ID, GOOGLE_CLIENT_SECRET);
            break;
    }
}

void OAuth::getToken(const QString url, const QString clientId, const QString clientSecret) {
    QUrl u(url);
    QNetworkRequest request(u);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("client_secret", clientSecret);

    if (!refreshing_) {
        query.addQueryItem("grant_type", "authorization_code");
        query.addQueryItem("code", ui->code->text());

        if (service_ == UploadService::GOOGLE) {
            query.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
        }
    } else {
        query.addQueryItem("grant_type", "refresh_token");
        query.addQueryItem("refresh_token", app_.settings().googleRefreshToken());
    }

    manager_.post(request, query.toString().toLatin1());
}
