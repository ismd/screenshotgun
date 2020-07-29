#pragma once

#include <QObject>

class AbstractService : public QObject {
    Q_OBJECT

public:
    AbstractService();

    virtual void upload(const QByteArray&) = 0;

signals:
    void onUploadSuccess(const QString&);
    void onUploadError(const QString&);

protected slots:
    void onUploadSuccess(const QString&) const;
    void onUploadError(const QString&) const;
};
