#include "Clipboard.h"
#include "src/Context.h"

#include <QClipboard>

Clipboard::Clipboard() {
}

void Clipboard::upload(const QImage& image) {
    QApplication::clipboard()->setImage(image);

    Context::getInstance().trayIcon->showMessage(
        "Screenshot is copied to the clipboard", "",
        QSystemTrayIcon::Information, 3000);

    emit uploadSuccess("");
}
