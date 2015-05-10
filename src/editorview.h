#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "editorform.h"
#include "newversion.h"
#include "server.h"
#include "settings.h"
#include "settingsform.h"
#include "trayicon.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    EditorView();
    QGraphicsScene* scene();
    SettingsForm* settingsForm();
    Server* server();

#ifdef Q_OS_WIN32
    bool nativeEvent(const QByteArray & eventType, void * message, long *result);
#endif

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void keyReleaseEvent(QKeyEvent*);

private slots:
    void run();
    void trayActivated(QSystemTrayIcon::ActivationReason);
    void checkVersion();
    void serverVersion(QString);
    void connectionError();
    void uploaded(QString);
    void uploadError();

private:
    void init();
    QPixmap _screenshot;
    QGraphicsScene* _scene;
    EditorForm* _editorForm;
    TrayIcon* _trayIcon;
    Settings _settings;
    SettingsForm* _settingsForm;
    Server* _server;
    NewVersion* _newVersion;
};

#endif // EDITORVIEW_H
