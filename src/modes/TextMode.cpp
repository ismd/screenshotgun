#include "../AppView.h"
#include "TextMode.h"

TextMode::TextMode(Scene& scene)
    : AbstractMode(scene),
      textArea_(new TextArea()),
      initialized_(false) {
    connect(&scene.sceneManager(), SIGNAL(modeChanged(ToolbarMode)),
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
    if (!initialized_) {
        textArea_->move(x, y);
    }
}

void TextMode::stop(int x, int y) {
    move(x, y);
    initialized_ = true;
    scene_.addWidget(textArea_);
    textArea_->setFocus();
}

void TextMode::clearFocus() {
    if (0 != textArea_) {
        textArea_->clearFocus();
        textArea_->setEnabled(false);
    }
}
