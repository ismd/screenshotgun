QT += widgets declarative quick

SOURCES += \
    main.cpp\
    server.cpp \
    editorview.cpp \
    editorform.cpp \
    modes/visibleareamode.cpp \
    modes/abstractmode.cpp \
    modes/linemode.cpp

HEADERS += \
    server.h \
    editorview.h \
    editorform.h \
    modes/visibleareamode.h \
    modes/abstractmode.h \
    modes/linemode.h

OTHER_FILES +=

RESOURCES +=

FORMS += \
    editorform.ui
