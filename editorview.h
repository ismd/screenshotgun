#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "visiblearea.h"
#include "editorform.h"
#include "modes/visibleareamode.h"

class EditorView : public QGraphicsView
{
public:
    EditorView();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    AbstractMode* getMode();
    void setMode(AbstractMode*);
    VisibleArea* getVisibleArea();

private:
    QPixmap screenshot;
    QGraphicsScene *scene;
    VisibleArea *visibleArea;
    AbstractMode *mode;
    EditorForm *editorForm;
};

#endif // EDITORVIEW_H
