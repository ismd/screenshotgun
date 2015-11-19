#include <QDebug>
#include "TextArea.h"

TextArea::TextArea(QWidget* parent) : QPlainTextEdit(parent) {
}

void TextArea::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return && event->modifiers().testFlag(Qt::ControlModifier)) {
        clearFocus();
        setEnabled(false);
    }
}
