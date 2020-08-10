#pragma once

#include <QImage>

class AbstractService : public QObject {
    Q_OBJECT

public:
    AbstractService();

    virtual void upload(const QImage&) = 0;

signals:
    void uploadSuccess(const QString&);
    void uploadError(const QString&);

protected slots:
    void onUploadSuccess(const QString&) const;
    void onUploadError(const QString&) const;
};
