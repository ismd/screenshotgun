#ifndef SCREENSHOTGUN_TEXTAREA_H
#define SCREENSHOTGUN_TEXTAREA_H

#include <QPlainTextEdit>

class TextArea : public QPlainTextEdit {

public:
    explicit TextArea(QWidget* parent = 0);

protected:
    void keyReleaseEvent(QKeyEvent*);
};

#endif //SCREENSHOTGUN_TEXTAREA_H
