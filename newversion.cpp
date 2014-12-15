#include <QFile>
#include "newversion.h"
#include "ui_newversion.h"

NewVersion::NewVersion(QWidget *parent, Server *server) :
    QDialog(parent),
    ui(new Ui::NewVersion),
    _server(server)
{
    connect(_server, SIGNAL(newVersionDownloaded(QByteArray)),
            this, SLOT(newVersionDownloaded(QByteArray)));

    ui->setupUi(this);
}

NewVersion::~NewVersion()
{
    delete ui;
}

void NewVersion::accept()
{
    _server->downloadNewVersion();
}

void NewVersion::newVersionDownloaded(QByteArray file)
{
    QString path = QApplication::applicationDirPath();

    #ifdef Q_OS_WIN32
    QString newFilename = path + "/open-screen-cloud-new.exe";
    #endif
    #ifndef Q_OS_WIN32
    QString newFilename = path + "/open-screen-cloud-new";
    #endif

    QFile newFile(newFilename);

    newFile.open(QIODevice::WriteOnly);
    newFile.write(file);
    newFile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    newFile.close();

    QProcess::startDetached(newFilename);
    exit(12);
}
