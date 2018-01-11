#ifndef SCREENSHOTGUN_TEXTMODE_H
#define SCREENSHOTGUN_TEXTMODE_H

#include "AbstractMode.h"
#include "TextArea.h"

class Overlay;

class TextMode : public AbstractMode {
    Q_OBJECT

public:
    TextMode(Overlay&);
    TextArea* textArea();

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private slots:
    void clearFocus();

private:
    TextArea* textArea_;
    bool initialized_;
};

#endif // SCREENSHOTGUN_TEXTMODE_H
