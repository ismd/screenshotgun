#pragma once

#include "lib/AbstractService.h"
#include "lib/UploadService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Google : public AbstractService {
    Q_OBJECT

public:
    explicit Google();

    void upload(const QImage&);
    void setToken(const QString&);
    void getFolder();

signals:
    void onRefreshToken(const UploadService);

private slots:
    void onUploadReply(QNetworkReply*);
    void onShareReply(QNetworkReply*);
    void onGetFolderReply(QNetworkReply*);
    void onCreateFolderReply(QNetworkReply*);
    void reupload();

private:
    void createFolder();

    QString token_;
    QNetworkAccessManager manager_;
    QString filename_;
    QString uploadLink_;
    const QImage* image_;
    bool needReupload_;
};
