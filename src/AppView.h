#ifndef SCREENSHOTGUN_APPVIEW_H
#define SCREENSHOTGUN_APPVIEW_H

#include <QGraphicsView>
#include "SceneManager.h"

#if defined(Q_OS_LINUX)
    #include "qxt/qxtglobalshortcut.h"
#elif defined(Q_OS_WIN32)
    #include <windows.h>
#endif

class App;

class AppView : public QGraphicsView {
    Q_OBJECT

public:
    explicit AppView(App&);
    ~AppView();

    App& app() const;
    SceneManager& sceneManager();
    Toolbar& toolbar();
    QPixmap& screenshot();
    void initShortcut();

public slots:
    void makeScreenshot();

private:
    App& app_;
    SceneManager sceneManager_;
    Toolbar toolbar_;
    QPixmap screenshot_;

#if defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#elif defined(Q_OS_WIN32)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
};

#endif //SCREENSHOTGUN_APPVIEW_H
