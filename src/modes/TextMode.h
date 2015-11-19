#ifndef SCREENSHOTGUN_TEXTMODE_H
#define SCREENSHOTGUN_TEXTMODE_H

#include <QPlainTextEdit>
#include "AbstractMode.h"

class AppView;

class TextMode : public AbstractMode {
    Q_OBJECT

public:
    TextMode(QGraphicsScene&, AppView&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private slots:
    void clearFocus();

private:
    QPlainTextEdit* text_;
    bool initialized_;
    AppView& appView_;
};

#endif // SCREENSHOTGUN_TEXTMODE_H
