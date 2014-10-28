#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include "editorform.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    EditorView();
    ~EditorView();
    QGraphicsScene* scene();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

private:
    QPixmap _screenshot;
    QGraphicsScene* _scene;
    EditorForm* _editorForm;
    QSystemTrayIcon* _trayIcon;
};

#endif // EDITORVIEW_H
