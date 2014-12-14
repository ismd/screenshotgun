QT += widgets network

SOURCES += \
    main.cpp\
    server.cpp \
    editorview.cpp \
    editorform.cpp \
    modes/visibleareamode.cpp \
    modes/abstractmode.cpp \
    modes/linemode.cpp \
    modes/rectmode.cpp \
    settings.cpp \
    newversion.cpp

HEADERS += \
    server.h \
    editorview.h \
    editorform.h \
    modes/visibleareamode.h \
    modes/abstractmode.h \
    modes/linemode.h \
    modes/rectmode.h \
    settings.h \
    const.h \
    newversion.h

OTHER_FILES +=

RESOURCES +=

FORMS += \
    settings.ui \
    editorform.ui \
    newversion.ui
