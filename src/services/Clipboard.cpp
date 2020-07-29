#include "Clipboard.h"
#include "src/Context.h"

#include <QClipboard>

Clipboard::Clipboard() {
}

void Clipboard::upload(const QByteArray& image) {
    QApplication::clipboard()->setImage(QImage(image));
    emit onUploadSuccess("");
}

void Clipboard::onUploadSuccess(const QString& url) {
  Context::getInstance().trayIcon.showMessage(
      "Screenshot is copied to the clipboard", "",
      QSystemTrayIcon::Information, 3000);
}
