#include <QFile>
#include "newversion.h"
#include "ui_newversion.h"
#include "updater.h"

NewVersion::NewVersion(QWidget *parent, Server *server) :
    QDialog(parent),
    ui(new Ui::NewVersion),
    _server(server)
{
    connect(_server, SIGNAL(newVersionDownloaded(QByteArray)),
            this, SLOT(newVersionDownloaded(QByteArray)));

    ui->setupUi(this);
    ui->progressBar->hide();
}

NewVersion::~NewVersion()
{
    delete ui;
}

void NewVersion::accept()
{
    ui->buttonBox->setDisabled(true);
    ui->progressBar->show();
    _server->downloadNewVersion();

    connect(_server, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(downloadProgress(qint64, qint64)));
}

void NewVersion::newVersionDownloaded(const QByteArray &file)
{
    Updater updater;
    updater.update(file);
}

void NewVersion::downloadProgress(qint64 read, qint64 total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(read);
}
