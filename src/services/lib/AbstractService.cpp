#include "AbstractService.h"
#include "src/Context.h"

#include <QClipboard>

AbstractService::AbstractService() {
    connect(this, &AbstractService::uploadSuccess, this, &AbstractService::onUploadSuccess);

    connect(this, &AbstractService::uploadError, this, &AbstractService::onUploadError);
}

void AbstractService::onUploadSuccess(const QString& url) const {
    if (url.isEmpty()) {
        return;
    }

    QApplication::clipboard()->setText(url);

    Context::getInstance().trayIcon->showMessage(
        "Link is copied to the clipboard", url,
        QSystemTrayIcon::Information, 3000);
}

void AbstractService::onUploadError(const QString& message) const {
    Context::getInstance().trayIcon->showMessage(
        "Error while uploading screenshot", message,
        QSystemTrayIcon::Critical, 10000);
}
