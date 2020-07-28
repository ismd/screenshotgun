#pragma once

#include <QPlainTextEdit>

class TextArea : public QPlainTextEdit {

public:
    explicit TextArea(QWidget* parent = 0);

protected:
    void keyReleaseEvent(QKeyEvent*);
};
