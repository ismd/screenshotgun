#ifndef NEWVERSION_H
#define NEWVERSION_H

#include <QDialog>
#include "server.h"

namespace Ui {
    class NewVersion;
}

class NewVersion : public QDialog
{
    Q_OBJECT

public:
    explicit NewVersion(QWidget *parent, Server*);
    ~NewVersion();

private slots:
    void accept();
    void newVersionDownloaded(const QByteArray&);
    void downloadProgress(qint64, qint64);

private:
    Ui::NewVersion *ui;
    Server* _server;
};

#endif // NEWVERSION_H
