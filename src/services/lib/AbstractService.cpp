#include "AbstractService.h"
#include "src/Context.h"

#include <QClipboard>

AbstractService::AbstractService() {
    // connect(this, SIGNAL(onUploadSuccess(const QString&)),
    //         this, SLOT(onUploadSuccess(const QString&)));

    // connect(this, SIGNAL(onUploadError(const QString&)),
    //         this, SLOT(onUploadError(const QString&)));
}

void AbstractService::onUploadSuccess(const QString& url) const {
    QApplication::clipboard()->setText(url);

    Context::getInstance().trayIcon.showMessage(
        "Link is copied to the clipboard", url,
        QSystemTrayIcon::Information, 3000);
}

void AbstractService::onUploadError(const QString& message) const {
    Context::getInstance().trayIcon.showMessage(
        "Error while uploading screenshot", message,
        QSystemTrayIcon::Critical, 10000);
}
