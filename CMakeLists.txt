cmake_minimum_required(VERSION 3.3)
project(screenshotgun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
    src/modes/abstractmode.cpp
    src/modes/abstractmode.h
    src/modes/arrowmode.cpp
    src/modes/arrowmode.h
    src/modes/linemode.cpp
    src/modes/linemode.h
    src/modes/rectmode.cpp
    src/modes/rectmode.h
    src/modes/visibleareamode.cpp
    src/modes/visibleareamode.h
    src/autostartup.cpp
    src/autostartup.h
    src/const.h
    src/editorform.cpp
    src/editorform.h
    src/editorview.cpp
    src/editorview.h
    src/main.cpp
    src/newversion.cpp
    src/newversion.h
    src/server.cpp
    src/server.h
    src/settings.cpp
    src/settings.h
    src/settingsform.cpp
    src/settingsform.h
    src/trayicon.cpp
    src/trayicon.h
    src/updater.cpp
    src/updater.h)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    find_package(Qt5 COMPONENTS Gui REQUIRED)
    include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

    list(APPEND SOURCE_FILES
        src/qxtglobal.h
        src/qxtglobalshortcut.h
        src/qxtglobalshortcut_p.h
        src/qxtglobalshortcut.cpp
        src/qxtglobalshortcut_x11.cpp)
endif()

qt5_wrap_ui(UIS_HDRS
    ui/editorform.ui
    ui/newversion.ui
    ui/settings.ui)

if(UNIX AND NOT APPLE)
    add_executable(screenshotgun ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun X11 Qt5::Widgets Qt5::Network)
else(WIN32)
    add_executable(screenshotgun WIN32 ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Network)
endif()
