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
    src/settings.cpp \
    src/newversion.cpp

HEADERS += \
    src/server.h \
    src/editorview.h \
    src/editorform.h \
    src/modes/visibleareamode.h \
    src/modes/abstractmode.h \
    src/modes/linemode.h \
    src/modes/rectmode.h \
    src/settings.h \
    src/const.h \
    src/newversion.h

OTHER_FILES +=

RESOURCES += \
    resources/res.qrc

FORMS += \
    ui/settings.ui \
    ui/editorform.ui \
    ui/newversion.ui
