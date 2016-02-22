#include "TextArea.h"

TextArea::TextArea() {
}

void TextArea::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return && event->modifiers().testFlag(Qt::ControlModifier)) {
        clearFocus();
        setEnabled(false);
    }
}
