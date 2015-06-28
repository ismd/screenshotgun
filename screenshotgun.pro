unix:!macx {
    INCLUDEPATH += /usr/include/qt/QtGui/$${QT_VERSION}/QtGui
    LIBS += -lX11

    HEADERS += \
        src/qxtglobal.h \
        src/qxtglobalshortcut.h \
        src/qxtglobalshortcut_p.h

    SOURCES += \
        src/qxtglobalshortcut.cpp \
        src/qxtglobalshortcut_x11.cpp
}

QT += widgets network

SOURCES += \
    src/main.cpp\
    src/server.cpp \
    src/editorview.cpp \
    src/editorform.cpp \
    src/modes/visibleareamode.cpp \
    src/modes/abstractmode.cpp \
    src/modes/linemode.cpp \
    src/modes/rectmode.cpp \
    src/newversion.cpp \
    src/updater.cpp \
    src/trayicon.cpp \
    src/autostartup.cpp \
    src/settingsform.cpp \
    src/settings.cpp \
    src/modes/arrowmode.cpp

HEADERS += \
    src/server.h \
    src/editorview.h \
    src/editorform.h \
    src/modes/visibleareamode.h \
    src/modes/abstractmode.h \
    src/modes/linemode.h \
    src/modes/rectmode.h \
    src/const.h \
    src/newversion.h \
    src/updater.h \
    src/trayicon.h \
    src/autostartup.h \
    src/settingsform.h \
    src/settings.h \
    src/modes/arrowmode.h

OTHER_FILES +=

RESOURCES += \
    resources/res.qrc

FORMS += \
    ui/settings.ui \
    ui/editorform.ui \
    ui/newversion.ui
