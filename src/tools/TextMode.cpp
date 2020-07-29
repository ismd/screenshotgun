#include "../Overlay.h"

TextMode::TextMode(Overlay& overlay)
    : AbstractMode(overlay),
      textArea_(0),
      initialized_(false) {
    connect(&overlay_, SIGNAL(toolChanged(ToolbarMode)),
            this, SLOT(clearFocus()));
}

TextArea* TextMode::textArea() {
    return textArea_;
}

void TextMode::init(int x, int y) {
    textArea_ = new TextArea();
    textArea_->setStyleSheet("background: transparent; border: 0;");
    textArea_->move(x, y);
}

void TextMode::move(int x, int y) {
    if (initialized_) {
        return;
    }

    textArea_->move(x, y);
}

void TextMode::stop(int x, int y) {
    move(x, y);
    initialized_ = true;
    overlay_.scene().addWidget(textArea_);
    textArea_->setFocus();
}

void TextMode::clearFocus() {
    if (0 != textArea_) {
        textArea_->clearFocus();
        textArea_->setEnabled(false);
    }
}
