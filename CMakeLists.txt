cmake_minimum_required(VERSION 3.3)
project(screenshotgun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
    src/modes/AbstractMode.cpp
    src/modes/AbstractMode.h
    src/modes/ArrowMode.cpp
    src/modes/ArrowMode.h
    src/modes/LineMode.cpp
    src/modes/LineMode.h
    src/modes/RectMode.cpp
    src/modes/RectMode.h
    src/modes/VisibleAreaMode.cpp
    src/modes/VisibleAreaMode.h
    src/Autostartup.cpp
    src/Autostartup.h
    src/Toolbar.cpp
    src/Toolbar.h
    src/App.cpp
    src/App.h
    src/main.cpp
    src/Server.cpp
    src/Server.h
    src/Settings.cpp
    src/Settings.h
    src/SettingsForm.cpp
    src/SettingsForm.h
    src/TrayIcon.cpp
    src/TrayIcon.h src/AppView.cpp src/AppView.h)

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
    ui/Toolbar.ui
    ui/NewVersion.ui
    ui/Settings.ui)

if(UNIX AND NOT APPLE)
    add_executable(screenshotgun ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun X11 Qt5::Widgets Qt5::Network)
else(WIN32)
    add_executable(screenshotgun WIN32 ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Network)
endif()
