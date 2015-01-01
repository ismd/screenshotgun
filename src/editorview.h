#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "editorform.h"
#include "settings.h"
#include "server.h"
#include "newversion.h"
#include "trayicon.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    EditorView();
    ~EditorView();
    QGraphicsScene* scene();
    Settings* settings();
    Server* server();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent*);

private slots:
    void run(QSystemTrayIcon::ActivationReason);
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
    Settings* _settings;
    Server* _server;
    NewVersion* _newVersion;
};

#endif // EDITORVIEW_H
