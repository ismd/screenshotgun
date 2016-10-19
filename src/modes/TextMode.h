#ifndef SCREENSHOTGUN_TEXTMODE_H
#define SCREENSHOTGUN_TEXTMODE_H

#include "AbstractMode.h"
#include "TextArea.h"

class AppView;

class TextMode : public AbstractMode {
    Q_OBJECT

public:
    TextMode(QGraphicsScene&, AppView&);
    TextArea* textArea();

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private slots:
    void clearFocus();

private:
    TextArea* textArea_;
    bool initialized_;
    AppView& appView_;
};

#endif // SCREENSHOTGUN_TEXTMODE_H
