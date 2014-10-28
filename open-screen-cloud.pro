QT += widgets network

SOURCES += \
    main.cpp\
    server.cpp \
    editorview.cpp \
    editorform.cpp \
    modes/visibleareamode.cpp \
    modes/abstractmode.cpp \
    modes/linemode.cpp \
    modes/rectmode.cpp

HEADERS += \
    server.h \
    editorview.h \
    editorform.h \
    modes/visibleareamode.h \
    modes/abstractmode.h \
    modes/linemode.h \
    modes/rectmode.h

OTHER_FILES +=

RESOURCES +=

FORMS += \
    editorform.ui
